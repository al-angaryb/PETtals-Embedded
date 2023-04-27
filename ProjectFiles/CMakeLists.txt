add_executable(main
    main.c
)

target_link_libraries(main
    pico_stdlib
    m6e_uhf_api
    servo_api
    )

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)
pico_add_extra_outputs(main)