cmake_minimum_required (VERSION 3.10)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

if (POLICY CMP0141)
  # cmake_policy(SET CMP0141 NEW)
  # set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("EvilGodSim")

option(ENGINE_BUILD_TESTS "Build tests" ON)
set(GAME_DIR "game" CACHE STRING "game direciory")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(IS_DEBUG_BUILD "false")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(IS_DEBUG_BUILD "true")
endif()


if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "cmake toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

set(ENTT_BUILD_DOCS OFF)

####################################### Resources #######################################

set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/${GAME_DIR}/resources")

file(GLOB_RECURSE RES_FILES CONFIGURE_DEPENDS
    ${RESOURCES_DIR}/*
)

add_custom_command(
    OUTPUT ${OUTPUT_DIR}/.stamp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT_DIR}/.stamp
    DEPENDS ${RES_FILES}
    COMMENT "Copying resources"
)

add_custom_target(copy_resources ALL
    DEPENDS ${OUTPUT_DIR}/.stamp
)

####################################### Subdirectories #######################################

add_subdirectory("${PROJECT_SOURCE_DIR}/libraries/glslcompiler")
add_subdirectory("${PROJECT_SOURCE_DIR}/libraries/rectpack2D")

add_subdirectory("engine")
add_subdirectory("editor")

if(ENGINE_BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory("tests")
endif()