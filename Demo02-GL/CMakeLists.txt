add_executable(Demo02-GL DemoGL.cpp)

target_link_libraries(Demo02-GL ionGraphicsGL)
target_link_libraries(Demo02-GL ionGraphics)
target_link_libraries(Demo02-GL ionWindow)
target_link_libraries(Demo02-GL ionFramework)
ExecutableDependencies(Demo02-GL)
