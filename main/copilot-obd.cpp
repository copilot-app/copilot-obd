#include <stdio.h>
#include <string.h>

#include "TinyGPS++.h"

#include <esp_log.h>
#include <esp_console.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include <driver/gpio.h>
#include <driver/uart.h>

#define GPS_RX GPIO_NUM_16
#define GPS_TX GPIO_NUM_17
#define GPS_UART UART_NUM_1

static const int RX_BUF_SIZE = 1024;

static TimerHandle_t timerGPS;

TinyGPSPlus gps;

void displayInfo() {
    printf("Location: ");
    if (gps.location.isValid()) {
        printf("%f", gps.location.lat());
        printf(",");
        printf("%f", gps.location.lng());
    } else
        printf("INVALID");

    printf("  Date/Time: ");
    if (gps.date.isValid()) {
        printf("%u", gps.date.month());
        printf("/");
        printf("%u", gps.date.day());
        printf("/");
        printf("%u", gps.date.year());
    } else {
        printf("INVALID");
    }

    printf(" ");
    if (gps.time.isValid()) {
        if (gps.time.hour() < 10)
            printf("0");
        printf("%u", gps.time.hour());
        printf(":");
        if (gps.time.minute() < 10)
            printf("0");
        printf("%u", gps.time.minute());
        printf(":");
        if (gps.time.second() < 10)
            printf("0");
        printf("%u", gps.time.second());
        printf(".");
        if (gps.time.centisecond() < 10)
            printf("0");
        printf("%u", gps.time.centisecond());
    } else {
        printf("INVALID");
    }

    printf("\n");
}

void init(void) {
    ESP_LOGI("UART", "Initializing UART");
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    // We won't use a buffer for sending data.
    uart_driver_install(GPS_UART, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(GPS_UART, &uart_config);
    uart_set_pin(GPS_UART, GPS_TX, GPS_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
int num = 0;
static void tx_task(void* arg) {
    char* Txdata = (char*)malloc(100);
    while (1) {
        sprintf(Txdata, "Hello world index = %d\r\n", num++);
        uart_write_bytes(GPS_UART, Txdata, strlen(Txdata));
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

static void rx_task(void* arg) {
    static const char* RX_TASK_TAG = "RX_TASK";
    ESP_LOGI(RX_TASK_TAG, "Rx task started");
    // esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*)malloc(RX_BUF_SIZE + 1);
    while (1) {
        const int rxBytes = uart_read_bytes(GPS_UART, data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            data[rxBytes] = 0;
            ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            if (gps.encode(*data)) {
                ESP_LOGI(RX_TASK_TAG, "Latitude: '%f'", gps.location.lat());
                ESP_LOGI(RX_TASK_TAG, "Longitude: '%f'", gps.location.lng());
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
    free(data);
    ESP_LOGI(RX_TASK_TAG, "Rx task finished");
}

void gpsTimerCallback(TimerHandle_t timer) {
    ESP_LOGD("GPS", "Timer callback");
    char* data = (char*)malloc(100);
}

void getLocationInfo(const char* data) {
    if (gps.encode(*data))
        displayInfo();
}

extern "C" void app_main(void) {
    ESP_LOGI("co tu sie dzieje", "pomocy");
    init();
    printf("L: %d\n", __LINE__);
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    // xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 2, NULL);

    // timerGPS = xTimerCreate("timerGPS", pdMS_TO_TICKS(5000), pdTRUE, (void*)0, gpsTimerCallback);
    // xTimerStart(timerGPS, 1);
}
