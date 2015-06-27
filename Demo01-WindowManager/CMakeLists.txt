add_executable(Demo01-WindowManager DemoWindowManager.cpp)

# Libraries
target_link_libraries(Demo01-WindowManager ionWindow)
target_link_libraries(Demo01-WindowManager ionGL)
target_link_libraries(Demo01-WindowManager ionFramework)
GLFW(Demo01-WindowManager)
GLEW(Demo01-WindowManager)
