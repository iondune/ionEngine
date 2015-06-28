add_executable(Demo03-Asset DemoAsset.cpp)

find_package(OpenGL REQUIRED)

# Libraries
target_link_libraries(Demo03-Asset ionAsset)
target_link_libraries(Demo03-Asset ionWindow)
target_link_libraries(Demo03-Asset ionGL)
target_link_libraries(Demo03-Asset ionFramework)
target_link_libraries(Demo03-Asset ${OPENGL_glu_LIBRARY})
GLFW(Demo03-Asset)
GLEW(Demo03-Asset)
