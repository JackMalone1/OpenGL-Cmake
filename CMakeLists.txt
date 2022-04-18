cmake_minimum_required(VERSION 3.17)

project(OpenGL)

find_package(glm CONFIG)

file(GLOB OpenGL_SRC CMAKE_CONFIGURE_DEPENDS
    "*.h"
    "*.cpp"
    "*.c"
)

add_executable(${PROJECT_NAME} ${OpenGL_SRC})

target_link_libraries(${PROJECT_NAME} GL dl glfw)