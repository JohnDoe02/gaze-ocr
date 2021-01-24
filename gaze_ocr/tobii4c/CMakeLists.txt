# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.17.2)
project (eyetracker)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

link_directories(/usr/lib/tobii/)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library(eyetracker eyetracker.cpp)
add_library(tobii_stream_engine SHARED IMPORTED)
set_property(TARGET tobii_stream_engine PROPERTY IMPORTED_LOCATION "/usr/lib/tobii/libtobii_stream_engine.so")
target_link_libraries(eyetracker tobii_stream_engine)

