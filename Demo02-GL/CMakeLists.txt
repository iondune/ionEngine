add_executable(Demo02-GL DemoGL.cpp)

target_link_libraries(Demo02-GL ionGraphicsGL)
target_link_libraries(Demo02-GL ionGraphics)
target_link_libraries(Demo02-GL ionWindow)
target_link_libraries(Demo02-GL ionFramework)
target_link_libraries(Demo02-GL ionCore)
ExecutableDependencies(Demo02-GL)
add_custom_command(
	TARGET Demo02-GL POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/Image.jpg $<TARGET_FILE_DIR:Demo02-GL>)
