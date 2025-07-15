cmake_minimum_required(VERSION 3.0)

project(mymuduo)

# 项目最终应该编译为动态库，设置动态库路径为项目根目录下的 bin 目录
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# 设置编译选项，调试信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 定义参与编译的源代码文件
aux_source_directory(. SRC_LIST)

# 编译为动态库
add_library(mymuduo SHARED ${SRC_LIST})



