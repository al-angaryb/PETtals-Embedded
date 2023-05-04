cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(lwip_import.cmake)

set(PICO_BOARD pico_w)
set(WIFI_SSID "NETGEAR60")
set(WIFI_PASSWORD "smilingviolin151")
set(TEST_TCP_SERVER_IP "192.168.0.2")

project(pettals C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(FreeRTOS)
# add_subdirectory(wolfssl)
add_subdirectory(ProjectFiles)
add_subdirectory(SERVO)
add_subdirectory(M6E)
add_subdirectory(BUTTON)