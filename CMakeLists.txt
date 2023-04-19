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
# add_subdirectory(MFRC522)
# add_subdirectory(BUTTON)
# add_subdirectory(M6E_API)
add_subdirectory(M6E)
add_executable(main
    main.c
)



# This is the linker if you are using the Mercury API and main_nonFunc.c.txt as the main file. 
# You will also need to include the M6E_API sub directory
# target_link_libraries(main 
#             pico_stdlib 
#             tm_reader
#             tmr_utils
#             tmr_strerror
#             tmr_param
#             tmr_loadsave_configuration
#             tm_reader_async
#             serial_transport
#             serial_reader
#             serial_reader_l3
#             osdep
#             llrp_reader
#             hex_bytes
#            )

target_link_libraries(main
    pico_stdlib
    m6e_uhf_api
    servo_api
    )

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)
pico_add_extra_outputs(main)


#add_subdirectory(./examples)


#For building, run this first: 
#       cmake -G "MinGW Makefiles" .. 
#           --Done in build folder






