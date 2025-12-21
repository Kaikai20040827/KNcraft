cmake_minimum_required(VERSION 3.26)

project(minecraft VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(minecraft
    src/app.cpp
    src/buffer.cpp
    src/camera.cpp
    src/input.cpp
    src/main.cpp
    src/mesh.cpp
    src/renderer.cpp
    src/shader.cpp
    src/texture.cpp
    src/stb_image.cpp
    src/chunk.cpp
    src/chunk_manager.cpp
    src/window.cpp
)

find_package(OpenGL REQUIRED)

target_include_directories(minecraft PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb
)

# Prefer static libraries (glew32s, glfw static) to avoid runtime DLL dependency.
add_definitions(-DGLEW_STATIC)



set(GLFW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib")
set(GLEW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/x64/glew32s.lib")

target_link_libraries(minecraft PRIVATE
    ${GLFW_LIB}
    ${GLEW_LIB}
    opengl32
    gdi32
    user32
    shell32
)

# Ensure static runtime linking for MSVC static libs if desired (optional)
# target_compile_options(minecraft PRIVATE /MT)
