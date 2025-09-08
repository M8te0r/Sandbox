cmake_minimum_required(VERSION 3.20)
project(CGSandbox VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -Wall ")
# set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -Wall -O3")

# 可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)


add_subdirectory(sandbox)




