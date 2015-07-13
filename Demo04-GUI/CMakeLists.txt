add_executable(Demo04-GUI DemoGUI.cpp)

find_package(OpenGL REQUIRED)

# Libraries
target_link_libraries(Demo04-GUI ionAsset)
target_link_libraries(Demo04-GUI ionWindow)
target_link_libraries(Demo04-GUI ionGL)
target_link_libraries(Demo04-GUI ionFramework)
target_link_libraries(Demo04-GUI ionGUI)
target_link_libraries(Demo04-GUI ${OPENGL_glu_LIBRARY})
GLFW(Demo04-GUI)
GLEW(Demo04-GUI)
