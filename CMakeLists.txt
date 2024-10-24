cmake_minimum_required(VERSION 3.29)
project(CG C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# ---------------------------------------------------------------------------

add_executable(teste testando.c)
target_link_libraries(teste ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

add_executable(hello_kitty hello_kitty.c)
target_link_libraries(hello_kitty ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

add_executable(esferas esferas.c stb_image.h)
target_link_libraries(esferas ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

# ---------------------------------------------------------------------------

add_executable(composicao
        composicao/main.c
        composicao/esfera.h
        composicao/cone.h
        composicao/esfera.c
        composicao/cubo.h
        composicao/cubo.c
        composicao/cone.c)
target_link_libraries(composicao ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

# ---------------------------------------------------------------------------

add_executable(rotacao
        rotacao/main.c
        rotacao/esfera.h
        rotacao/cone.h
        rotacao/esfera.c
        rotacao/cubo.h
        rotacao/cubo.c
        rotacao/cone.c)
target_link_libraries(rotacao ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)
