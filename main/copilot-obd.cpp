#include "r_gps.h"
#include "r_uart.h"

extern "C" void app_main(void) {
    if (initGPS())
        startUart();
}
