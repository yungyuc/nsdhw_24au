cmake_minimum_required(VERSION 3.0)
project(_vector)

# Find Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Find Pybind11
find_package(pybind11 REQUIRED)

# Add the example module
pybind11_add_module(_matrix src/_matrix.cpp)

# Link the module with Python
target_link_libraries(_matrix PRIVATE ${PYTHON_LIBRARIES})
