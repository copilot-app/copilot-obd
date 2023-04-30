#include "r_gps.h"

#include <esp_log.h>

#include "r_uart.h"

static const char* kGpsTag = "GPS";

static void parseGPSData(char* data, int len) {
    ESP_LOGD(kGpsTag, "Parsing GPS data");
}

static void uartGPSCallback(UartId id, char* data, int len) {
    parseGPSData(data, len);
}

bool initGPS() {
    ESP_LOGI(kGpsTag, "Initializing GPS");
    return initUart(kUartGPS, uartGPSCallback);
}
