cmake_minimum_required(VERSION 3.29)
project(CG C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(teste testando.c)
target_link_libraries(teste ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

add_executable(hello_kitty hello_kitty.c)
target_link_libraries(hello_kitty ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

add_executable(argentinian_apple esferas.c stb_image.h)
target_link_libraries(argentinian_apple ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)