#pragma once

#include "Common.hpp"

void configureUartPort(UartConfiguration configuration);
void startUartTxTransmission(uart_port_t portNumber);
void startUartRxTransmission(RxTaskParameters *parameters);
