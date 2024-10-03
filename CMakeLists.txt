cmake_minimum_required(VERSION 3.29)
project(CG C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(circulo testando.c)

target_link_libraries(circulo ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

