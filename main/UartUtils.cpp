#include "UartUtils.hpp"

// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include <esp_log.h>


static void rxTask(void* parameters) {
    auto [portNumber, callback] = *(RxTaskParameters*)parameters;
    char* dataBuffer = new char[rxBufferSize + 1];
    ESP_LOGI(__func__, "Task created for %d port", portNumber);

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
    ESP_LOGI(__func__, "Task deleted for %d port", portNumber);
}

void configureUartPort(UartConfiguration configuration) {
    auto [portNumber, txPin, rxPin, uartConfig] = configuration;
    ESP_LOGI(__func__, "Port number %d", portNumber);

    uart_driver_install(portNumber, rxBufferSize * 2, 0, 0, NULL, 0);
    uart_param_config(portNumber, &uartConfig);
    uart_set_pin(portNumber, txPin, rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    ESP_LOGI(__func__, "Port number %d configured", portNumber);
}

void startUartRxTransmission(RxTaskParameters* parameters) {
    ESP_LOGI(__func__, "On port number %d", parameters->portNumber);

    xTaskCreate(rxTask, "uart_rx_task", 1024 * 2, (void*)parameters, configMAX_PRIORITIES, NULL);

    ESP_LOGI(__func__, "Transmission on port number %d started", parameters->portNumber);
}
