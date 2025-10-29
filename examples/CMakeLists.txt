file(GLOB EXAMPLES_SRC *.cpp)
add_executable(GeoAlgoExample ${EXAMPLES_SRC})
target_link_libraries(GeoAlgoExample PRIVATE GeoAlgo)
