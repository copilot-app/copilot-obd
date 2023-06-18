#include "UartUtils.hpp"

#include <cstring>

// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include <esp_log.h>

void configureUartPort(UartConfiguration configuration) {
    auto [portNumber, txPin, rxPin, uartConfig] = configuration;
    ESP_LOGI(__func__, "[%s] Port number %d", UartPortToString[portNumber].c_str(), portNumber);

    ESP_ERROR_CHECK(uart_driver_install(portNumber, 2048, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(portNumber, &uartConfig));
    ESP_ERROR_CHECK(uart_set_pin(portNumber, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_LOGI(__func__, "[%s] Port number %d configured", UartPortToString[portNumber].c_str(), portNumber);
}

static void txTask(void* parameters) {
    uart_port_t portNumber = (uart_port_t)parameters;
    const char* loraMessage = "Hello, LoRa! Lorem ipsum dolor sit amet, consectetur adipiscing elit.";

    while (true) {
        int txBytes = uart_write_bytes(portNumber, loraMessage, strlen(loraMessage));
        ESP_LOGD(__func__, "Wrote %d bytes: '%s'", txBytes, loraMessage);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void rxTask(void* parameters) {
    auto [portNumber, callback] = *(RxTaskParameters*)parameters;
    char* dataBuffer = new char[rxBufferSize + 1];
    ESP_LOGI(__func__, "[%s] Task created for port %d", UartPortToString[portNumber].c_str(), portNumber);

    while (true) {
        const int dataSize = uart_read_bytes(portNumber, dataBuffer, rxBufferSize, 1000 / portTICK_PERIOD_MS);
        if (dataSize > 0) {
            dataBuffer[dataSize] = 0;
            ESP_LOGI(__func__, "Read %d bytes: '%s'", dataSize, dataBuffer);
            if (callback) {
                callback(dataBuffer, dataSize);
            }
        }
    }

    delete (RxTaskParameters*)parameters;
    delete[] dataBuffer;
    ESP_LOGI(__func__, "[%s] Task deleted for port %d", UartPortToString[portNumber].c_str(), portNumber);
}

void startUartTxTransmission(uart_port_t portNumber) {
    ESP_LOGI(__func__, "[%s] On port number %d", UartPortToString[portNumber].c_str(), portNumber);

    std::string taskName = std::string("uart_tx_task_") + std::to_string(portNumber);
    xTaskCreate(txTask, taskName.c_str(), 1024 * 2, (void*)portNumber, configMAX_PRIORITIES, NULL);

    ESP_LOGI(__func__, "[%s] Transmission on port number %d started", UartPortToString[portNumber].c_str(), portNumber);
}

void startUartRxTransmission(RxTaskParameters* parameters) {
    auto portNumber = parameters->portNumber;
    ESP_LOGI(__func__, "[%s] On port number %d", UartPortToString[portNumber].c_str(), portNumber);

    std::string taskName = std::string("uart_rx_task_") + std::to_string(portNumber);
    xTaskCreate(rxTask, taskName.c_str(), 1024 * 2, (void*)parameters, configMAX_PRIORITIES, NULL);

    ESP_LOGI(__func__, "[%s] Transmission on port number %d started", UartPortToString[portNumber].c_str(), portNumber);
}
