#include "GpsService.hpp"

#include <string.h>

#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include <esp_log.h>

#include "TinyGPS++.h"

TinyGPSPlus gps;

void parseGpsData(char* data, size_t size) {
    ESP_LOGI(__func__, "Parsing data");
    while (*data) {
        if (!gps.encode(*data++))
            continue;

        if (!gps.location.isValid())
            continue;

        ESP_LOGI(__func__, "Location: %f, %f", gps.location.lat(), gps.location.lng());
        return;
    }
    
    ESP_LOGI(__func__, "Data not parsed");
}
