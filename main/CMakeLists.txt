add_executable(main main.c)

pico_generate_pio_header(main ${CMAKE_CURRENT_LIST_DIR}/hello.pio)

target_sources(main PRIVATE)

 # Create map/bin/hex file etc.
 pico_add_extra_outputs(main)

 # Import pico_stdlib which imports commonly used features

 target_link_libraries(main PRIVATE pico_stdlib hardware_pio)

 pico_set_binary_type(main no_flash)
 pico_add_extra_outputs(main)

 # Add path via pico_set_program_url CMAKE
 example_auto_set_url(main)





