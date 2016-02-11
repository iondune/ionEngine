add_executable(Demo04-Scene DemoScene.cpp)

# Libraries
target_link_libraries(Demo04-Scene ionScene)
target_link_libraries(Demo04-Scene ionGraphicsGL)
target_link_libraries(Demo04-Scene ionGraphics)
target_link_libraries(Demo04-Scene ionWindow)
target_link_libraries(Demo04-Scene ionFramework)
GLFW(Demo04-Scene)
GLEW(Demo04-Scene)
