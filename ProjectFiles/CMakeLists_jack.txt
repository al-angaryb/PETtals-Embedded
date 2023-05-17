
add_executable(main
            main.c
            ${PICO_LWIP_CONTRIB_PATH}/apps/ping/ping.c
            )
    target_compile_definitions(main PRIVATE
            WIFI_SSID=\"${WIFI_SSID}\"
            WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
            )
    target_include_directories(main PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}
            ${CMAKE_CURRENT_LIST_DIR}/../.. # for our common lwipopts
            ${PICO_LWIP_CONTRIB_PATH}/apps/ping
            )

target_link_libraries(main
    pico_stdlib
    hardware_irq
    m6e_uhf_api
    servo_api
    hardware_gpio 
    hardware_pwm 
    hardware_clocks
    pico_lwip_iperf
    pico_cyw43_arch_lwip_threadsafe_background
    freertos
    FreeRTOS
    task 
    stdio 
    )

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)
pico_add_extra_outputs(main)