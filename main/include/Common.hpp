#pragma once

#include <map>
#include <string>

#include <driver/gpio.h>
#include <driver/uart.h>

const unsigned rxBufferSize = 1024;

typedef unsigned PinId;

typedef enum {
    UartIdGps = UART_NUM_1,
    UartIdLora = UART_NUM_1,
    UartIdLora2 = UART_NUM_2,
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
