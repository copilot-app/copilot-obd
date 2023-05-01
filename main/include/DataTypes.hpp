#pragma once

#include <driver/gpio.h>
#include <driver/uart.h>

const unsigned rxBufferSize = 1024;

typedef unsigned PinId;

typedef enum {
    kUartIdGps = UART_NUM_1,
    // sentinel
    kUartIdLast
} UartId;
typedef void (*RxCallback)(char* data, size_t size);

struct UartConfiguration {
    UartId portNumber;
    PinId txPin;
    PinId rxPin;
    uart_config_t configuration;
};

struct RxTaskParameters {
    UartId portNumber;
    RxCallback callback;
};
