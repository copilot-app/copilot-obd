#pragma once

#include <map>
#include <string>

#include <driver/gpio.h>
#include <driver/uart.h>

const unsigned rxBufferSize = 1024;

typedef unsigned PinId;

typedef enum {
    UartIdGps = UART_NUM_1,
} UartId;

struct UartConfiguration {
    UartId portNumber;
    PinId txPin;
    PinId rxPin;
    uart_config_t configuration;
};

typedef void (*RxCallback)(char* data, size_t size, char* location);
struct RxTaskParameters {
    UartId portNumber;
    RxCallback callback;
    char* location;
};

extern std::map<UartId, std::string> UartIdToString;
