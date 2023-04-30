#pragma once

#include <driver/gpio.h>
#include <driver/uart.h>

const int rxBufferSize = 1024;

typedef int PinId;
typedef int UartId;
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
