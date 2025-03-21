cmake_minimum_required(VERSION 3.5)

project (Game)
set(EXECUTABLE_NAME "EvilGodSimulator")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${EXECUTABLE_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
)

target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
        Engine::Core
)

