# 指定 cmake 版本，跟安装的版本保持一致
cmake_minimum_required(VERSION 3.4.1)
 
# 指定 c++ 标准
set(CMAKE_CXX_STANDARD 11)
 
# 输出编译信息
message("Hello !!! Start compile!")
 
# 设置源码根路径，即 cpp 目录
set(SRC_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
message(${SRC_ROOT_PATH})
 
# 定义要编译的文件列表变量
file(GLOB CPP_FILES "*.cpp" "*.c")
 
# 设置要编译的源文件
set(
        SOURCE_FILES
        ${CPP_FILES}
)
 
# include 头文件目录
include_directories(${SRC_ROOT_PATH}/inc)

LINK_DIRECTORIES($(SRC_ROOT_PATH))
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)
LINK_LIBRARIES(pthread)
# LINK_LIBRARIES(boost_system) 
# LINK_LIBRARIES(boost_iostreams) 
LINK_LIBRARIES(jakaAPI)
 
# 编译成可执行文件，如果编译动态库可以用：target_link_libraries
add_executable(dlltest ${SOURCE_FILES})