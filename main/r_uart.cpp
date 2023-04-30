#include "r_uart.h"

#include <string.h>

#include <esp_log.h>
#include <esp_console.h>

#include <driver/gpio.h>
#include <driver/uart.h>

#define GPS_RX GPIO_NUM_16
#define GPS_TX GPIO_NUM_17
#define GPS_UART UART_NUM_1

static const int RX_BUF_SIZE = 1024;

static const char* kUartTag = "UART";

struct {
    rxCallback gpsCallback;
    rxCallback loraCallback;
} eventUartCallbacks;

struct EventUart {
    UartId id;
    char data[RX_BUF_SIZE + 1];
} eventUart;

static void rxGPSTask(void* arg) {
    ESP_LOGD(__func__, "Rx task started");
    ESP_LOGD(kUartTag, "Rx task started");
    while (true) {
        const int rxBytes = uart_read_bytes(GPS_UART, eventUart.data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            eventUart.data[rxBytes] = 0;
            eventUartCallbacks.gpsCallback(kUartGPS, eventUart.data, rxBytes);
            ESP_LOGD(kUartTag, "Read %d bytes: '%s'", rxBytes, eventUart.data);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGD(kUartTag, "Rx task terminated");
}

bool initUart(UartId id, rxCallback callback) {
    ESP_LOGI(__func__, "Initializing UART");
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    switch (id) {
    case kUartGPS:
        uart_driver_install(GPS_UART, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
        uart_param_config(GPS_UART, &uart_config);
        uart_set_pin(GPS_UART, GPS_TX, GPS_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
        eventUartCallbacks.gpsCallback = callback;
        return true;

    case kUartLORA:
        // uart_driver_install(LORA_UART, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
        // uart_param_config(LORA_UART, &uart_config);
        // uart_set_pin(LORA_UART, LORA_TX, LORA_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
        // eventUartCallbacks.loraCallback = callback;
        return true;

    default:
        return false;
    }
}

void startUart(void) {
    ESP_LOGI("UART", "Starting UART");
    if (eventUartCallbacks.gpsCallback) {
        xTaskCreate(rxGPSTask, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
    } else {
        ESP_LOGE("UART", "Failed to initialize GPS UART");
    }

    // if (eventUartCallbacks.loraCallback) {
    //     xTaskCreate(rxLORATask, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
    // xTaskCreate(txLORATask, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    // } else {
    //     ESP_LOGE("UART", "Failed to initialize LORA UART");
    // }
}
