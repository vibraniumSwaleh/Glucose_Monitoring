aux_source_directory(. DIR_Fonts_SRCS)

# 生成链接库
add_library(GImage ${DIR_Fonts_SRCS})