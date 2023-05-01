#include "GpsService.hpp"

#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include <esp_log.h>

#include "TinyGPS++.h"

TinyGPSPlus gps;

void parseGpsData(char* data, size_t size) {
    ESP_LOGI(__func__, "Parsing data");
        ESP_LOGD(__func__, "Data: %s", data);
    if (gps.encode(*data)){
        if (gps.location.isValid())
            ESP_LOGI(__func__, "Location: %f, %f", gps.location.lat(), gps.location.lng());
    } else {
        ESP_LOGI(__func__, "Data not parsed");
    }
}
