add_executable(Demo02-GL DemoGL.cpp)

find_package(OpenGL REQUIRED)

# Libraries
target_link_libraries(Demo02-GL ionWindow)
target_link_libraries(Demo02-GL ionGL)
target_link_libraries(Demo02-GL ionFramework)
target_link_libraries(Demo02-GL ${OPENGL_glu_LIBRARY})
GLFW(Demo02-GL)
GLEW(Demo02-GL)
