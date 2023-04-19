
add_library(m6e_uhf_api STATIC
    ${CMAKE_CURRENT_LIST_DIR}./m6e_uhf_api.c
    ${CMAKE_CURRENT_LIST_DIR}./m6e_uhf_api.h
    )

# target_include_directories(m6e_uhf_api 
#     ${CMAKE_CURRENT_LIST_DIR}
#     )
target_link_libraries(m6e_uhf_api 
    pico_stdlib
    hardware_uart
    pico_time
    )
# pico_enable_stdio_usb(m6e_uhf_api 1)
# pico_enable_stdio_uart(m6e_uhf_api 1)