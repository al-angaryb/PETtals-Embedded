include_directories(include)


add_library(hex_bytes STATIC
    ${CMAKE_CURRENT_LIST_DIR}./hex_bytes.c
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    )
# target_link_directories(hex_bytes INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(llrp_reader_l3 STATIC
    ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_l3.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
    )
# target_link_directories(llrp_reader_l3 INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(llrp_reader STATIC
    ${CMAKE_CURRENT_LIST_DIR}./llrp_reader.c
    # ${CMAKE_CURRENT_LIST_DIR}./include/tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./include/osdep.h
    # ${CMAKE_CURRENT_LIST_DIR}./include/tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./include/tmr_llrp_reader.h 
    # ${CMAKE_CURRENT_LIST_DIR}./include/llrp_reader_imp.h 
    )
# target_link_directories(llrp_reader INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(osdep STATIC
    ${CMAKE_CURRENT_LIST_DIR}./osdep.c
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
    )
target_link_libraries(osdep
    pico_time
    hardware_irq
    )

# target_link_directories(osdep INTERFACE
#     pico_time
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )



add_library(serial_reader_l3 STATIC
    ${CMAKE_CURRENT_LIST_DIR}./serial_reader_l3.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_imp.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h 
    )
# target_link_directories(serial_reader_l3 INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(serial_reader STATIC
    ${CMAKE_CURRENT_LIST_DIR}./serial_reader.c
    
)
# target_link_directories(serial_reader INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
#     # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
#     )


add_library(serial_transport STATIC
    ${CMAKE_CURRENT_LIST_DIR}./serial_transport.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    )
target_link_libraries(serial_transport
    hardware_uart
    pico_stdlib
    )   
# target_link_directories(serial_transport INTERFACE
#     hardware_uart
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(tm_reader_async INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tm_reader_async.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./tm_config.h
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h
    # ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_imp.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h
    )
# target_link_directories(tm_reader_async INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(tm_reader STATIC
    ${CMAKE_CURRENT_LIST_DIR}./tm_reader.c
   
    )
# target_link_directories(tm_reader INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     # ${CMAKE_CURRENT_LIST_DIR}./tm_config.h
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_types.h
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_status.h
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_gpio.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_params.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_read_plan.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_auth.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_data.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_data.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_lock_action.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_protocol.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_tagop.h
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_serial_reader.h 
#     # ${CMAKE_CURRENT_LIST_DIR}./tmr_llrp_reader.h 
#     )


add_library(tmr_loadsave_configuration STATIC
    ${CMAKE_CURRENT_LIST_DIR}./tmr_loadsave_configuration.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h 
    )
# target_link_directories(tmr_loadsave_configuration INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(tmr_param STATIC
    ${CMAKE_CURRENT_LIST_DIR}./tmr_param.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    )
# target_link_directories(tmr_param INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(tmr_strerror STATIC
    ${CMAKE_CURRENT_LIST_DIR}./tmr_strerror.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    )
# target_link_directories(tmr_strerror INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )


add_library(tmr_utils STATIC
    ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.c
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_types.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h 
    )
# target_link_directories(tmr_utils INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/include
#     )
