add_executable(Demo04-Scene DemoScene.cpp)

target_link_libraries(Demo04-Scene ionScene)
target_link_libraries(Demo04-Scene ionGraphicsGL)
target_link_libraries(Demo04-Scene ionGraphics)
target_link_libraries(Demo04-Scene ionWindow)
target_link_libraries(Demo04-Scene ionFramework)
target_link_libraries(Demo04-Scene ionCore)
ExecutableDependencies(Demo04-Scene)
add_custom_command(
	TARGET Demo04-Scene POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/Diffuse.vert $<TARGET_FILE_DIR:Demo04-Scene>)
add_custom_command(
	TARGET Demo04-Scene POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/Diffuse.frag $<TARGET_FILE_DIR:Demo04-Scene>)
