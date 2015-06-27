# CMake
cmake_minimum_required(VERSION 2.6)
project(ionEngine)

# Compiler Settings
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Include")
set(CMAKE_CXX_FLAGS "-std=c++11")

# Output Directories
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Function Library
function(GLFW)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIRS})
	target_link_libraries(DeploymentTest ${GLFW_LIBRARIES})
	target_link_libraries(DeploymentTest ${GLFW_STATIC_LIBRARIES})
endfunction(GLFW)

function(GLEW)
	find_package(GLEW REQUIRED)
	if (GLEW_FOUND)
		include_directories(${GLEW_INCLUDE_DIRS})
		target_link_libraries(DeploymentTest ${GLEW_LIBRARIES})
	endif()
endfunction(GLEW)

# Builds
add_subdirectory("ionFramework")
add_subdirectory("DeploymentTest")
add_subdirectory("UnitTests")
