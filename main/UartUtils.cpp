#include "UartUtils.hpp"

#include <cstring>

// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include <esp_log.h>

static void rxTask(void* parameters) {
    auto [portNumber, callback] = *(RxTaskParameters*)parameters;
    char* dataBuffer = new char[rxBufferSize + 1];
    ESP_LOGI(__func__, "[%s] Task created for port %d", UartIdToString[portNumber].c_str(), portNumber);

    while (true) {
        const int dataSize = uart_read_bytes(portNumber, dataBuffer, rxBufferSize, 500 / portTICK_PERIOD_MS);
        if (dataSize > 0) {
            dataBuffer[dataSize] = 0;
            ESP_LOGD(__func__, "Read %d bytes: '%s'", dataSize, dataBuffer);
            callback(dataBuffer, dataSize);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    delete (RxTaskParameters*)parameters;
    delete[] dataBuffer;
    ESP_LOGI(__func__, "[%s] Task deleted for port %d", UartIdToString[portNumber].c_str(), portNumber);
}

void configureUartPort(UartConfiguration configuration) {
    auto [portNumber, txPin, rxPin, uartConfig] = configuration;
    ESP_LOGI(__func__, "[%s] Port number %d", UartIdToString[portNumber].c_str(), portNumber);

    ESP_ERROR_CHECK(uart_driver_install(portNumber, 2048, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(portNumber, &uartConfig));
    ESP_ERROR_CHECK(uart_set_pin(portNumber, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_LOGI(__func__, "[%s] Port number %d configured", UartIdToString[portNumber].c_str(), portNumber);
}

void startUartRxTransmission(RxTaskParameters* parameters) {
    auto portNumber = parameters->portNumber;
    ESP_LOGI(__func__, "[%s] On port number %d", UartIdToString[portNumber].c_str(), portNumber);

    std::string taskName = std::string("uart_rx_task_") + std::to_string(portNumber);
    xTaskCreate(rxTask, taskName.c_str(), 1024 * 2, (void*)parameters, configMAX_PRIORITIES, NULL);

    ESP_LOGI(__func__, "[%s] Transmission on port number %d started", UartIdToString[portNumber].c_str(), portNumber);
}
