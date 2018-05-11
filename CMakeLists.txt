
set(ION_ENGINE_VERSION 0.4.5)

# CMake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ionEngine VERSION ${ION_VERSION} LANGUAGES CXX)

include(GNUInstallDirs)

# Output Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ION_ENGINE_DIRECTORY "${PROJECT_SOURCE_DIR}")

# Build Properties
function(BuildProperties TargetName)

	# Compiler Settings
	target_compile_options(${TargetName} PUBLIC "-std=c++1y")

	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Include")

	# Dependencies
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies/stb")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies/tinyformat")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies/glm")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies/imgui")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies/Catch/single_include")
	target_include_directories(${TargetName} PUBLIC "${ION_ENGINE_DIRECTORY}/Dependencies/glad/include")

	# Definitions
	target_compile_definitions(${TargetName} PRIVATE -DION_PROJECT_BASE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/")

endfunction(BuildProperties)

# Executable Properties
function(ExecutableProperties TargetName)

	# OpenGL
	find_package(OpenGL REQUIRED)
	if (OPENGL_FOUND)
		target_link_libraries(${TargetName} ${OPENGL_LIBRARIES})
	endif()

	# GLFW
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	target_include_directories(${TargetName} PRIVATE ${GLFW_INCLUDE_DIRS})
	target_link_libraries(${TargetName} ${GLFW_LIBRARIES})
	target_link_libraries(${TargetName} ${GLFW_STATIC_LIBRARIES})

endfunction(ExecutableProperties)


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
