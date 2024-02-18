cmake_minimum_required(VERSION 3.27)
project(Engine2)

set(CMAKE_CXX_STANDARD 17)

# Find X11 and OpenGL libraries
find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories for header files
include_directories(${X11_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

# Add executable target
add_executable(Engine2
        main.cpp
        SystemClass.cpp
        SystemClass.h
        ApplicationClass.cpp
        ApplicationClass.h
        OpenGLClass.cpp
        OpenGLClass.h
        InputClass.cpp
        InputClass.h
        ColorShaderClass.cpp
        ColorShaderClass.h
        ModelClass.cpp
        ModelClass.h
        CameraClass.cpp
        CameraClass.h)

# Linking libraries
target_link_libraries(Engine2 PRIVATE ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
