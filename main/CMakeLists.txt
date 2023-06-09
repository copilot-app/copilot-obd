idf_component_register(
    SRCS            "main.cpp"
                    "Common.cpp"
                    "GpsService.cpp"
                    "UartUtils.cpp"
                    "Bluetooth.cpp"

    INCLUDE_DIRS    "include"

    REQUIRES        bt driver nvs_flash TinyGPSPlus-ESPIDF
)
