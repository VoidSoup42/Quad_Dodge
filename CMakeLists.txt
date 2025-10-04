cmake_minimum_required(VERSION 3.10.0)
project(Quad_Dodge VERSION 0.1.0 LANGUAGES C CXX)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Quad_Dodge
    src/Main.cpp
    src/Application.h
    src/Application.cpp
)

target_link_libraries(Quad_Dodge PRIVATE OpenGL::GL GLEW::GLEW glfw)