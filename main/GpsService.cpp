#include "GpsService.hpp"

// #define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include <esp_log.h>

#include "TinyGPS++.h"

TinyGPSPlus gps;

/**
 * Parses GPS data and prints out the latitude and longitude
 * @param data data to parse
 * @param size size of data
 */
void parseGpsData(char* data, size_t size, char* location) {
    ESP_LOGI(__func__, "Parsing data");

    while (*data) {
        if (gps.encode(*data++) && gps.location.isValid()) {
            sprintf(location, "%f,%f", gps.location.lat(), gps.location.lng());
            ESP_LOGI(__func__, "Location: %f, %f", gps.location.lat(), gps.location.lng());
            return;
        }
    }
    
    ESP_LOGI(__func__, "Data not parsed");
}
