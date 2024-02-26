cmake_minimum_required(VERSION 3.27)
project(Engine2)

set(CMAKE_CXX_STANDARD 17)

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories for header files
include_directories(${X11_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(final)