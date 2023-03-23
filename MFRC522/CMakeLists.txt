#MFRC CMakeLists

add_executable(rfid_test
        rfid_test.c)

target_link_libraries(rfid_test
        pico_stdlib
        pico_binary_info
        hardware_spi       
        )

target_include_directories(rfid_test PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}
        )

# pico_sdk_init()
pico_enable_stdio_usb(rfid_test 1)
pico_enable_stdio_uart(rfid_test 0)

pico_add_extra_outputs(rfid_test)

