#pragma once

#include <map>
#include <string>

#include <driver/gpio.h>
#include <driver/uart.h>

const unsigned rxBufferSize = 1024;

typedef unsigned PinId;

typedef enum {
    UartIdLora = UART_NUM_1,
    UartIdGps = UART_NUM_1,
} UartId;

struct UartConfiguration {
    UartId portNumber;
    PinId txPin;
    PinId rxPin;
    uart_config_t configuration;
};

typedef void (*RxCallback)(char* data, size_t size);
struct RxTaskParameters {
    UartId portNumber;
    RxCallback callback;
};

extern std::map<UartId, std::string> UartIdToString;
