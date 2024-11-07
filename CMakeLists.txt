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


# ---------------------------------------------------------------------------
add_executable(esferas esferas/esferas.c stb_image.h)

set(METAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/esferas/metal.png")
set(WOOD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/esferas/wood.png")
add_custom_command(
    TARGET esferas POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${METAL_PATH}" "$<TARGET_FILE_DIR:esferas>"
        "${WOOD_PATH}" "$<TARGET_FILE_DIR:esferas>"
)

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

# ---------------------------------------------------------------------------

add_executable(bule
        bule/bule.c
        bule/bule.h
)
target_link_libraries(bule ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)

# ---------------------------------------------------------------------------

add_executable(transf
        transformações/bules.c stb_image.h transformações/textura.jpg
)

set(TEXTURA_PATH "${CMAKE_CURRENT_SOURCE_DIR}/transformações/textura.jpg")
add_custom_command(
    TARGET transf POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${TEXTURA_PATH}" "$<TARGET_FILE_DIR:transf>"
)

target_link_libraries(transf ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)