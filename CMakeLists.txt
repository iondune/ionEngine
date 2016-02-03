# CMake
cmake_minimum_required(VERSION 2.6)
project(ionEngine)

# Output Directories
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Compiler Settings
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Include")
set(CMAKE_CXX_FLAGS "-std=c++11")

# Libraries
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/stb")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/tinyformat")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/glm")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/imgui")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/Catch/include")

function(GLFW TargetName)

	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW example tests")
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW example docs")
	add_subdirectory("${PROJECT_SOURCE_DIR}/Dependencies/glfw" "${PROJECT_SOURCE_DIR}/Dependencies/glfw/bin")

	include_directories("${PROJECT_SOURCE_DIR}/Dependencies/glfw/include")
	target_link_libraries(${TargetName} glfw ${GLFW_LIBRARIES})
	target_link_libraries(${TargetName} glfw ${GLFW_STATIC_LIBRARIES})

	#find_package(PkgConfig REQUIRED)
	#pkg_search_module(GLFW REQUIRED glfw3)
	#include_directories(${GLFW_INCLUDE_DIRS})
	#target_link_libraries(${TargetName} ${GLFW_LIBRARIES})
	#target_link_libraries(${TargetName} ${GLFW_STATIC_LIBRARIES})

endfunction(GLFW)

function(GLEW TargetName)

	find_package(OpenGL REQUIRED)
	if (OPENGL_FOUND)
		target_link_libraries(${TargetName} ${OPENGL_LIBRARIES})
	endif()
	find_package(GLEW REQUIRED)
	if (GLEW_FOUND)
		include_directories(${GLEW_INCLUDE_DIRS})
		target_link_libraries(${TargetName} ${GLEW_LIBRARIES})
		target_link_libraries(${TargetName} ${OPENGL_LIBRARIES})
	endif()

endfunction(GLEW)

#########
# Build #
#########

# Libraries
add_subdirectory("ionFramework")
# add_subdirectory("ionGraphics")
# add_subdirectory("ionAsset")
# add_subdirectory("ionWindow")
# add_subdirectory("ionGUI")
# add_subdirectory("ionScene")
# add_subdirectory("ionScience")
# add_subdirectory("ionBootstrap")

# Tests
add_subdirectory("DeploymentTest")
add_subdirectory("UnitTests")
