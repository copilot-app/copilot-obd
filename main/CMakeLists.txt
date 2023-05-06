idf_component_register(
    SRCS            "main.cpp"
                    "Common.cpp"
                    "GpsService.cpp"
                    "UartUtils.cpp"
                    "Bluetooth.cpp"

    INCLUDE_DIRS    "include"
                    ${CMAKE_SOURCE_DIR}/components/TinyGPSPlus-ESPIDF/TinyGPSPlus/src/
                    $ENV{IDF_PATH}/components/bt/host/bluedroid/api/include/api/

    REQUIRES        bt driver nvs_flash
)
