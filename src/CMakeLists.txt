file(GLOB HEADER_LIST "../include/*.h")
file(GLOB SOURCE_LIST "*.cpp")

set(GLAD_HEADER "../include/glad/glad.h")

add_library(glad ${HEADER_LIST} glad.c)
add_library(total ${HEADER_LIST} ${SOURCE_LIST})

target_include_directories(total PUBLIC "../include")
target_include_directories(glad PUBLIC "../include/glad")
target_link_libraries(total PRIVATE ${X11_LIBRARIES} ${OPENGL_LIBRARIES})

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)
