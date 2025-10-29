# example_nurbs
add_executable(example_nurbs example_nurbs.cpp)
target_link_libraries(example_nurbs PRIVATE GeoAlgo)

# example_curve
add_executable(example_curve example_curve.cpp)
target_link_libraries(example_curve PRIVATE GeoAlgo)
