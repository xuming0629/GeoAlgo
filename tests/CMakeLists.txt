file(GLOB TEST_SRC *.cpp)
add_executable(GeoAlgoTests ${TEST_SRC})
target_link_libraries(GeoAlgoTests PRIVATE GeoAlgo)
