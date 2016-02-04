add_executable(Demo03-GUI DemoGUI.cpp)

# Libraries
target_link_libraries(Demo03-GUI ionGUI)
target_link_libraries(Demo03-GUI ionGraphicsGL)
target_link_libraries(Demo03-GUI ionGraphics)
target_link_libraries(Demo03-GUI ionWindow)
target_link_libraries(Demo03-GUI ionFramework)
GLFW(Demo03-GUI)
GLEW(Demo03-GUI)
