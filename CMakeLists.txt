cmake_minimum_required (VERSION 3.10)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

if (POLICY CMP0141)
  # cmake_policy(SET CMP0141 NEW)
  # set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("EvilGodSim")

option(ENGINE_BUILD_TESTS "Build tests" ON)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(IS_DEBUG_BUILD "false")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(IS_DEBUG_BUILD "true")
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "cmake toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

set(ENTT_BUILD_DOCS OFF)

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