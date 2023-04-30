#include <stdio.h>

#include "TinyGPS++.h"

#include <esp_log.h>
#include <esp_console.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include <driver/gpio.h>

#define GPIO_RX GPIO_NUM_3
#define GPIO_TX GPIO_NUM_1

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

void tinygpsplus_example() {
    const char* gpsStream =
        "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
        "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
        "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
        "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
        "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
        "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";

    while (*gpsStream)
        if (gps.encode(*gpsStream++))
            displayInfo();
}

extern "C" void app_main(void) {
    
}
