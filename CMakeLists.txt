
set(ION_ENGINE_VERSION 0.4.2)

# CMake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ionEngine VERSION ${ION_VERSION} LANGUAGES CXX)

include(GNUInstallDirs)

# Output Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler Settings
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

# Dependencies
include_directories("${PROJECT_SOURCE_DIR}/Dependencies")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/stb")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/tinyformat")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/glm")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/imgui")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/Catch/include")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/glad/include")

function(ExecutableDependencies TargetName)
	# OpenGL
	find_package(OpenGL REQUIRED)
	if (OPENGL_FOUND)
		target_link_libraries(${TargetName} ${OPENGL_LIBRARIES})
	endif()

	# GLFW
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIRS})
	target_link_libraries(${TargetName} ${GLFW_LIBRARIES})
	target_link_libraries(${TargetName} ${GLFW_STATIC_LIBRARIES})
endfunction(ExecutableDependencies)

#########
# Build #
#########

# Libraries
add_subdirectory("ionCore")
add_subdirectory("ionWindow")
add_subdirectory("ionGraphics")
add_subdirectory("ionGraphicsGL")
add_subdirectory("ionGUI")
add_subdirectory("ionScene")
add_subdirectory("ionApplication")
add_subdirectory("ionAnimation")
add_subdirectory("ionScience")

# Tests
add_subdirectory("TestConfig")
add_subdirectory("TestDeployment")
add_subdirectory("TestUnits")

# Demos
add_subdirectory("Demo01-WindowManager")
add_subdirectory("Demo02-GL")
add_subdirectory("Demo03-GUI")
add_subdirectory("Demo04-Scene")
add_subdirectory("Demo05-Application")
