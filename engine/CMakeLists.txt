cmake_minimum_required(VERSION 3.5)

project(Engine)

####################################### Branding #######################################

set(Project_CommonName "EvilGodEngine")

set(Project_Copyright "EvilGod Contributors")
set(Project_Domain "https://192.0.0.1")
set(Project_Name "${Project_CommonName}")
set(Project_DisplayName "${Project_CommonName} 5")
set(Project_UserAgent "${Project_CommonName}/5.0")
set(Project_ConfigFile "evilgodengine.cfg")
set(Project_Git "https://github.com/NiNeDelixe/EvilGodSim")

set(Project_Branding_ICNS "${PROJECT_SOURCE_DIR}/branding/${Project_CommonName}.icns")
set(Project_Branding_WindowsRC "${PROJECT_SOURCE_DIR}/branding/multimc.rc")
set(Project_Branding_Logo "${PROJECT_SOURCE_DIR}/branding/logo.ico")

set(Project_META_URL "https://meta.multimc.org/v1/")
set(Project_PASTE_EE_API_KEY "utLvciUouSURFzfjPxLBf5W4ISsUX4pwBDF7N1AfZ")
set(Project_MSA_CLIENT_ID "499546d9-bbfe-4b9b-a086-eb3d75afb78f")
set(Project_IMGUR_CLIENT_ID "5b97b0713fba4a3")
set(Project_BUG_TRACKER_URL "${Project_Git}/issues")


add_subdirectory("buildconfig")
add_subdirectory("resources")
add_subdirectory("libraries/glslcompiler" EXCLUDE_FROM_ALL)
add_subdirectory("libraries/rectpack2D" EXCLUDE_FROM_ALL)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE MODULES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.ixx")

add_library (${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} ${MODULES})
add_library (Engine::Core ALIAS ${PROJECT_NAME})

include_directories("${PROJECT_SOURCE_DIR}/include" "libraries/rectpack2D/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include" "libraries/rectpack2D/src")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(toml11 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(glog REQUIRED)
find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")
find_package(imgui CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		BuildConfig
		OpenGL::GL
		glfw
		GLEW::glew
		toml11::toml11
		opencv_core
		opencv_imgproc
		opencv_imgcodecs
		opencv_highgui
		glog::glog
		glsl::compiler
		EmbeddedResourcesEngine
		${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS}
		imgui::imgui
		EnTT::EnTT
)