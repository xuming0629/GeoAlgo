cmake_minimum_required(VERSION 3.15)
project(GeoAlgo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------
# 使用系统 Python3
# --------------------------
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Using Python3: ${Python3_EXECUTABLE}")
include_directories(${Python3_INCLUDE_DIRS})

# --------------------------
# pybind11
# --------------------------
find_package(pybind11 REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include)

# --------------------------
# GeoAlgo 库
# --------------------------
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB GEOALGO_SRC src/*.cpp)
file(GLOB GEOALGO_HEADERS include/*.h)

add_library(GeoAlgo STATIC ${GEOALGO_SRC} ${GEOALGO_HEADERS})
target_include_directories(GeoAlgo PUBLIC ${PROJECT_SOURCE_DIR}/include)

# --------------------------
# 测试和示例
# --------------------------
add_subdirectory(tests)
add_subdirectory(examples)
