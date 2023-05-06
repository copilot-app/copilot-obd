#include "Common.hpp"
#include "GpsService.hpp"
#include "UartUtils.hpp"
#include "Bluetooth.hpp"

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

extern "C" void app_main(void) {
    esp_log_level_set("*", ESP_LOG_DEBUG);
    configureUartPort(gpsUartConfiguration);
    startUartRxTransmission(new RxTaskParameters{ gpsUartConfiguration.portNumber, parseGpsData });
}
