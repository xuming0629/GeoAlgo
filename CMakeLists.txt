cmake_minimum_required(VERSION 3.15)
project(GeoAlgo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件收集
file(GLOB GEOALGO_SRC src/*.cpp)
file(GLOB GEOALGO_HEADERS include/*.h)

# 生成静态库
add_library(GeoAlgo STATIC ${GEOALGO_SRC} ${GEOALGO_HEADERS})

# 测试与示例
add_subdirectory(tests)
add_subdirectory(examples)
