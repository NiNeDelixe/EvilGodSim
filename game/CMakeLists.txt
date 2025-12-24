cmake_minimum_required(VERSION 3.10)

project(Game)
set(EXECUTABLE_NAME "EvilGodSimulator")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.h")

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${EXECUTABLE_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
)

find_package(unofficial-noise CONFIG REQUIRED)
find_package(unofficial-noiseutils CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glog REQUIRED)

target_link_libraries(${EXECUTABLE_NAME}
    PUBLIC
        Engine::Core
        unofficial::noise::noise
		unofficial::noiseutils::noiseutils
        imgui::imgui
        glog::glog
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "${CMAKE_CURRENT_BINARY_DIR}/resources"
)

#file(GLOB_RECURSE RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources/*")
#file(COPY ${RESOURCES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")

