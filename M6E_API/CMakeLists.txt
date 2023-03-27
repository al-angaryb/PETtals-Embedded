add_library(hex_bytes INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./hex_bytes.c
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    )
target_link_directories(hex_bytes INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(llrp_reader_l3 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_l3.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
    )
target_link_directories(llrp_reader_l3 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(llrp_reader INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./llrp_reader.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_llrp_reader.h 
    # ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_imp.h 
    )
target_link_directories(llrp_reader INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(osdep_picow INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./osdep_picow.c
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
    )
target_link_directories(osdep_picow INTERFACE
    pico_time
    ${CMAKE_CURRENT_LIST_DIR}/include
    )



add_library(serial_reader_l3 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./serial_reader_l3.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_imp.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h 
    )
target_link_directories(serial_reader_l3 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(serial_reader INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./serial_reader.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h
)
target_link_directories(serial_reader INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(serial_transport_picow INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./serial_transport_picow.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    )
target_link_directories(serial_transport_picow INTERFACE
    hardware_uart
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(tm_reader_async INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tm_reader_async.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./tm_config.h
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h
    # ${CMAKE_CURRENT_LIST_DIR}./llrp_reader_imp.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h
    )
target_link_directories(tm_reader_async INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(tm_reader INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tm_reader.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_config.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_types.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_status.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_gpio.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_params.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_read_plan.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_auth.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_data.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_data.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_lock_action.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_tag_protocol.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_tagop.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_serial_reader.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_llrp_reader.h 
    )
target_link_directories(tm_reader INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(tmr_loadsave_configuration INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tmr_loadsave_configuration.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./serial_reader_imp.h 
    )
target_link_directories(tmr_loadsave_configuration INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(tmr_param INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tmr_param.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    )
target_link_directories(tmr_param INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(tmr_strerror INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tmr_strerror.c
    # ${CMAKE_CURRENT_LIST_DIR}./tm_reader.h
    )
target_link_directories(tmr_strerror INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )


add_library(tmr_utils INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.c
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_types.h 
    # ${CMAKE_CURRENT_LIST_DIR}./tmr_utils.h 
    # ${CMAKE_CURRENT_LIST_DIR}./osdep.h 
    )
target_link_directories(tmr_utils INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )
