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

	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIRS})
	target_link_libraries(${TargetName} ${GLFW_LIBRARIES})
	target_link_libraries(${TargetName} ${GLFW_STATIC_LIBRARIES})

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
add_subdirectory("ionWindow")
add_subdirectory("ionGraphics")
add_subdirectory("ionGraphicsGL")
add_subdirectory("ionGUI")
add_subdirectory("ionScene")
add_subdirectory("ionAnimation")
# add_subdirectory("ionScience")

# Tests
add_subdirectory("TestDeployment")
add_subdirectory("TestUnits")

# Demos
add_subdirectory("Demo01-WindowManager")
add_subdirectory("Demo02-GL")
add_subdirectory("Demo03-GUI")
add_subdirectory("Demo04-Scene")
