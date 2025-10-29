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


# 安装到 build/install
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install path" FORCE)
endif()
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

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


# --------------------------
# 安装规则
# --------------------------
# 安装静态库
install(TARGETS GeoAlgo
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# 安装头文件（可选，重复 install PUBLIC_HEADER 时可省略）
install(DIRECTORY include/ DESTINATION include)

# 安装 example 可执行文件
# 自动查找 examples 子目录下所有 cpp 文件生成的可执行文件
file(GLOB EXAMPLE_BIN examples/*.cpp)
foreach(example_file ${EXAMPLE_BIN})
    get_filename_component(example_name ${example_file} NAME_WE)
    install(TARGETS ${example_name} RUNTIME DESTINATION bin)
endforeach()

