cmake_minimum_required(VERSION 3.0)
project(_vector)

# Find Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Find Pybind11
find_package(pybind11 REQUIRED)
set(ENV{MKLROOT} "/opt/intel/oneapi/mkl/latest/")
find_package(MKL CONFIG REQUIRED PATHS $ENV{MKLROOT})
#message(STATUS "${MKL_IMPORTED_TARGETS}") #Provides available list of targets based on input

# Add the example module
pybind11_add_module(_matrix src/_matrix.cpp)

# Link the module with Python
target_link_libraries(_matrix PRIVATE ${PYTHON_LIBRARIES})

target_compile_options(_matrix PRIVATE $<TARGET_PROPERTY:MKL::MKL,INTERFACE_COMPILE_OPTIONS>)
target_include_directories(_matrix PUBLIC $<TARGET_PROPERTY:MKL::MKL,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(_matrix PUBLIC $<LINK_ONLY:MKL::MKL>)


