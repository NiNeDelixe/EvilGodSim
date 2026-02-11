cmake_minimum_required(VERSION 3.10)

project(Engine)

####################################### Options #######################################

option(ENGINE_USE_WINDOWS_HEADER "Use windows header for modding on win, may sending some warnigs from glfw3" ON)

set(ENTT_INCLUDE_NATVIS ON)

####################################### Branding #######################################

set(ENGINE_Project_CommonName "EvilGodEngine")

set(ENGINE_Project_Copyright "EvilGod Contributors")
set(ENGINE_Project_Domain "https://192.0.0.1")
set(ENGINE_Project_Name "${ENGINE_Project_CommonName}")
set(ENGINE_Project_DisplayName "${ENGINE_Project_CommonName} 5")
set(ENGINE_Project_UserAgent "${ENGINE_Project_CommonName}/5.0")
set(ENGINE_Project_ConfigFile "evilgodengine.cfg")
set(ENGINE_Project_Git "https://github.com/NiNeDelixe/EvilGodSim")

set(ENGINE_Project_Branding_ICNS "${PROJECT_SOURCE_DIR}/branding/${ENGINE_Project_CommonName}.icns")
set(ENGINE_Project_Branding_WindowsRC "${PROJECT_SOURCE_DIR}/branding/multimc.rc")
set(ENGINE_Project_Branding_Logo "${PROJECT_SOURCE_DIR}/branding/logo.ico")

set(ENGINE_Project_META_URL "https://meta.multimc.org/v1/")
set(ENGINE_Project_PASTE_EE_API_KEY "utLvciUouSURFzfjPxLBf5W4ISsUX4pwBDF7N1AfZ")
set(ENGINE_Project_MSA_CLIENT_ID "499546d9-bbfe-4b9b-a086-eb3d75afb78f")
set(ENGINE_Project_IMGUR_CLIENT_ID "5b97b0713fba4a3")
set(ENGINE_Project_BUG_TRACKER_URL "${ENGINE_Project_Git}/issues")


add_subdirectory("buildconfig")
add_subdirectory("resources")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE MODULES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.ixx")

add_library (${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
add_library (Engine::Core ALIAS ${PROJECT_NAME})

include_directories("${PROJECT_SOURCE_DIR}/include" 
	"${PROJECT_SOURCE_DIR}/libraries/rectpack2D/src"
	"${PROJECT_SOURCE_DIR}/libraries/fpm/include"
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(toml11 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(glog REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(fixed_math REQUIRED)
find_package(eventpp CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(cpptrace CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
	"libraries/rectpack2D/src"
	"libraries/fpm/include"
	${Stb_INCLUDE_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_precompile_headers(${PROJECT_NAME} PUBLIC <fixed_math/fixed_math.hpp>)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		BuildConfig
		OpenGL::GL
		glfw
		GLEW::glew
		toml11::toml11
		opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui
		glog::glog
		glsl::compiler
		EmbeddedResourcesEngine
		imgui::imgui
		EnTT::EnTT
		assimp::assimp
		fixed_math::fixed_math
		rectpack2D::rectpack2D
		eventpp::eventpp
		TBB::tbb TBB::tbbmalloc TBB::tbbmalloc_proxy
		cpptrace::cpptrace
		magic_enum::magic_enum
)

if(${ENGINE_USE_WINDOWS_HEADER})
	target_compile_definitions(${PROJECT_NAME} PUBLIC -DENGINE_USE_WINDOWS_HEADER)	
endif(${ENGINE_USE_WINDOWS_HEADER})