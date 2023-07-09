cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
project(main)

set(PICO_BOARD pico_w)

pico_sdk_init()

#添加编译子目录
add_subdirectory(lib/Config)
add_subdirectory(lib/OLED)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)
add_subdirectory(lib/GImage)
add_subdirectory(lib/Menu)

#添加头文件目录
include_directories(./lib/Config)
include_directories(./lib/GUI)
include_directories(./lib/OLED)
include_directories(./lib/GImage)
include_directories(./lib/Menu)

# 生成可执行文件
add_executable(main main.cpp)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

target_link_libraries(main 
    OLED 
    Menu 
    GUI 
    Fonts 
    GImage 
    Config 
    pico_stdlib 
    hardware_spi 
    hardware_adc
    pico_cyw43_arch_none
    pico_multicore
    )