add_executable(Demo02-GL DemoGL.cpp)

# Libraries
target_link_libraries(Demo02-GL ionGraphicsGL)
target_link_libraries(Demo02-GL ionGraphics)
target_link_libraries(Demo02-GL ionWindow)
target_link_libraries(Demo02-GL ionFramework)
GLFW(Demo02-GL)
GLEW(Demo02-GL)
