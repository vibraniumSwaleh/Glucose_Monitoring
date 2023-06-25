aux_source_directory(. DIR_Menu_SRCS)

include_directories(../Config)
include_directories(../GUI)
include_directories(../OLED)
include_directories(../GImage)

# 生成链接库
add_library(Menu ${DIR_Menu_SRCS})
target_link_libraries(Menu PUBLIC Config GUI OLED GImage)