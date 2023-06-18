#pragma once

#include <map>
#include <string>

#include <driver/gpio.h>
#include <driver/uart.h>

const unsigned rxBufferSize = 512;

typedef unsigned PinId;

struct UartConfiguration {
    uart_port_t portNumber;
    PinId txPin;
    PinId rxPin;
    uart_config_t configuration;
};

typedef void (*RxCallback)(char* data, size_t size);
struct RxTaskParameters {
    uart_port_t portNumber;
    RxCallback callback;
};

extern std::map<uart_port_t, std::string> UartPortToString;
