
add_executable(button_test
        button_test.c)
        
target_link_libraries(button_test
        pico_stdlib 
        hardware_gpio 
        hardware_irq
        )




target_include_directories(button_test PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        )



pico_enable_stdio_usb(button_test 1)
pico_enable_stdio_uart(button_test 0)

pico_add_extra_outputs(button_test)

