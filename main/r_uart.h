#ifndef _R_UART_H_
#define _R_UART_H_


typedef enum {
    kUartGPS = 0,
    kUartLORA,
    // sentinel
    kUartLast
} UartId;

typedef void (*rxCallback)(UartId id, char* data, int len);
bool initUart(UartId id, rxCallback callback);

void startUart();

#endif // _R_UART_H_
