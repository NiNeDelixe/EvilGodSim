cmake_minimum_required(VERSION 3.10)
project(EmbeddedResourcesEngine)

set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE TEXTURE_FILES 
    LIST_DIRECTORIES false 
    RELATIVE "${CMAKE_SOURCE_DIR}" 
    "textures/*.png"
)

file(GLOB_RECURSE SHADERS_FILES 
    LIST_DIRECTORIES false 
    RELATIVE "${CMAKE_SOURCE_DIR}" 
    "shaders/*.vert" "shaders/*.frag"
)

set(EMBEDDED_RESOURCES_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${EMBEDDED_RESOURCES_DIR}")

function(convert_to_embedded_resource input_file output_h template)
    file(READ "${input_file}" file_data HEX)
    
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " byte_array "${file_data}")
    
    get_filename_component(var_name "${input_file}" NAME_WE)
    #string(MAKE_C_IDENTIFIER "${input_file}" var_name)
    string(REPLACE "/" "_" var_name "${var_name}")
    string(REPLACE "." "_" var_name "${var_name}")
    
    configure_file(
        ${template}
        "${output_h}"
        @ONLY
    )
endfunction()

set(TEXTURES_TEMPLATE "textures_template.h.in")
set(SHADERS_TEMPLATE "shaders_template.h.in")

############## Textures
foreach(texture_file ${TEXTURE_FILES})
    get_filename_component(texture_name "${texture_file}" NAME_WE)
    set(output_h "${EMBEDDED_RESOURCES_DIR}/${texture_name}.h")
    convert_to_embedded_resource("${CMAKE_SOURCE_DIR}/${texture_file}" "${output_h}" ${TEXTURES_TEMPLATE})
    list(APPEND GENERATED_HEADERS "${output_h}")
endforeach()

############## Shaders
foreach(file ${SHADERS_FILES})
    message(STATUS "shader file: ${file}")

    get_filename_component(shader_name "${file}" NAME_WE)
    get_filename_component(shader_ext "${file}" EXT)
    string(REPLACE "." "_" shader_ext "${shader_ext}")
    set(var_name "${shader_name}${shader_ext}")  # main_vert

    # Читаем исходный код шейдера
    file(READ ${CMAKE_SOURCE_DIR}/${file} shader_code)

    # Генерируем .h-файл из шаблона
    configure_file(
        ${SHADERS_TEMPLATE}
        "${EMBEDDED_RESOURCES_DIR}/${var_name}.h"
        @ONLY
    )
    
    #get_filename_component(file_name "${file}" NAME_WE)
    #convert_to_embedded_resource("${CMAKE_SOURCE_DIR}/${file}" "${output_h}" ${SHADERS_TEMPLATE})
    list(APPEND GENERATED_HEADERS "${output_h}")
endforeach()

add_library(${PROJECT_NAME} INTERFACE
    ${GENERATED_HEADERS}
    ${EMBEDDED_RESOURCES_DIR}
)

target_include_directories(${PROJECT_NAME} INTERFACE "${GENERATED_HEADERS}" "${EMBEDDED_RESOURCES_DIR}")

message(STATUS "generated headers: ${GENERATED_HEADERS}")
message(STATUS "resources dir: ${EMBEDDED_RESOURCES_DIR}")