cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(PICO_BOARD pico_w)
set(WIFI_SSID "NETGEAR60")
set(WIFI_PASSWORD "smilingviolin151")
set(TEST_TCP_SERVER_IP "192.168.0.1")

project(api C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# set(API_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()
# include_directories("VSARM/sdk/pico/pico-sdk/src/rp2_common/pico_stdlib")

add_subdirectory(SERVO)
add_subdirectory(MFRC522)
add_subdirectory(BUTTON)

add_library(READER)

# add_executable(main
#     main.c
# )

# pico_enable_stdio_usb(main 1)
# pico_enable_stdio_uart(main 0)


# target_link_libraries(main 
#             pico_stdlib 
#             hardware_gpio 
#             hardware_pwm 
#             hardware_clocks)




# pico_add_extra_outputs(main)


#add_subdirectory(./examples)


#For building, run this first: 
#       cmake -G "MinGW Makefiles" .. 
#           --Done in build folder






