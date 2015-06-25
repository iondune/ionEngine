cmake_minimum_required(VERSION 2.6)
project(DeploymentTest)
add_executable(DeploymentTest DeploymentTest.cpp)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(DeploymentTest ${GLFW_LIBRARIES})
target_link_libraries(DeploymentTest ${GLFW_STATIC_LIBRARIES})

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(DeploymentTest ${GLEW_LIBRARIES})
endif()

# ionEngine
include_directories(../Include/)
set(CMAKE_CXX_FLAGS "-std=c++11")

