cmake_minimum_required(VERSION 3.5)

project(Editor)
set(EXECUTABLE_NAME "EvilGodEngineEditor")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

if (WIN32)
set_target_properties(${EXECUTABLE_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
)
endif()

find_package(imgui CONFIG REQUIRED)

target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
        Engine::Core
        imgui::imgui
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")

