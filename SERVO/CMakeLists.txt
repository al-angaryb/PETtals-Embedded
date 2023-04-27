add_library(servo_api  
        ${CMAKE_CURRENT_LIST_DIR}./servo_api.c
        ${CMAKE_CURRENT_LIST_DIR}./servo_api.h
        )
# add_executable(servo_test
#         servo_test.c)
target_include_directories(servo_api PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(servo_api 
        pico_stdlib 
        hardware_gpio 
        hardware_pwm
        hardware_clocks
        hardware_irq
        )

# target_include_directories(servo_test PUBLIC
#         ${CMAKE_CURRENT_LIST_DIR}
#         )


# pico_enable_stdio_usb(servo_test 1)
# pico_enable_stdio_uart(servo_test 0)

# pico_add_extra_outputs(servo_test)

