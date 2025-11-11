# -------------------------
# NURBS 示例
# -------------------------
add_executable(example_nurbs example_nurbs.cpp)
target_link_libraries(example_nurbs PRIVATE GeoAlgo)
target_include_directories(example_nurbs PRIVATE ${PROJECT_SOURCE_DIR}/include)

# -------------------------
# Curve 示例
# -------------------------
add_executable(example_curve example_curve.cpp)
target_link_libraries(example_curve PRIVATE GeoAlgo)
target_include_directories(example_curve PRIVATE ${PROJECT_SOURCE_DIR}/include)

# -------------------------
# Python 绘图示例
# -------------------------
add_executable(example_plot example_plot.cpp)
target_link_libraries(example_plot PRIVATE GeoAlgo pybind11::embed ${Python3_LIBRARIES})
target_include_directories(example_plot PRIVATE ${PROJECT_SOURCE_DIR}/include ${Python3_INCLUDE_DIRS})


add_executable(test_horner test_horner.cpp)
add_executable(test_bernstein test_bernstein.cpp)
add_executable(test_bezier test_bezier.cpp)
target_link_libraries(test_bezier PRIVATE GeoAlgo pybind11::embed ${Python3_LIBRARIES})

#-------------------
add_executable(example_power_basis example_power_basis.cpp)
target_link_libraries(example_power_basis PRIVATE GeoAlgo)
target_include_directories(example_power_basis PRIVATE ${PROJECT_SOURCE_DIR}/include)


