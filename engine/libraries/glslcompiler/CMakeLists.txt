cmake_minimum_required(VERSION 3.10)
project(GLSLCompiler)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

add_library(glsl_compiler ${SOURCES} ${HEADERS})
add_library(glsl::compiler ALIAS glsl_compiler)

target_include_directories(glsl_compiler PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(glsl_compiler
    PRIVATE
        OpenGL::GL
)