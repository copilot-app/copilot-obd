#include "Common.hpp"
#include "GpsService.hpp"
#include "UartUtils.hpp"

#include <cstring>
#include <esp_log.h>

UartConfiguration gpsUartConfiguration = {
    .portNumber = UartIdGps,
    .txPin = GPIO_NUM_17,
    .rxPin = GPIO_NUM_16,
    .configuration = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_APB,
    }
};

UartConfiguration lora2UartConfiguration = {
    .portNumber = UartIdLora2,
    .txPin = GPIO_NUM_17,
    .rxPin = GPIO_NUM_16,
    .configuration = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
    }
};

void txTask(void*) {
    uart_port_t uart_num = UART_NUM_0;

    uart_config_t uart_config = {
            .baud_rate = 9600,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_driver_install(uart_num, 2048, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, GPIO_NUM_10, GPIO_NUM_9, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    const char* loraMessage = "Hello, LoRa!\n";

    while (true) {
        ESP_ERROR_CHECK(uart_write_bytes(uart_num, loraMessage, std::strlen(loraMessage)));
    }
}

extern "C" void app_main(void) {
    esp_log_level_set("*", ESP_LOG_DEBUG);

    xTaskCreate(txTask, "txTask", 2048, NULL, 10, NULL);
}
