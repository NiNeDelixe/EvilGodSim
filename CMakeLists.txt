cmake_minimum_required (VERSION 3.10)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("EvilGodSim")

option(BUILD_TESTS "Build tests" OFF)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(IS_DEBUG_BUILD "false")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(IS_DEBUG_BUILD "true")
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "cmake toolchin file: ${CMAKE_TOOLCHAIN_FILE}")

set(${ENTT_BUILD_DOCS} ON)

####################################### Subdirectories #######################################

add_subdirectory("Engine" EXCLUDE_FROM_ALL)
add_subdirectory("Game")
add_subdirectory("Editor")

if(BUILD_TESTS)
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory("tests")
endif()