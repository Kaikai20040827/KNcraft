cmake_minimum_required(VERSION 3.26)

project(KNCraft VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC
    src/*.cpp
)

add_executable(KNCraft
    ${SRC}
)

find_package(OpenGL REQUIRED)

target_include_directories(KNCraft PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/stb
)

# Prefer static libraries (glew32s, glfw static) to avoid runtime DLL dependency.
add_definitions(-DGLEW_STATIC)

set(GLFW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-vc2022/glfw3.lib")
set(GLEW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/x64/glew32s.lib")


target_link_libraries(KNCraft PRIVATE
    ${GLFW_LIB}
    ${GLEW_LIB}

    opengl32
    gdi32
    user32
    shell32
)

