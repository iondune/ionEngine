add_executable(Demo03-GUI DemoGUI.cpp)

target_link_libraries(Demo03-GUI ionGUI)
target_link_libraries(Demo03-GUI ionGraphicsGL)
target_link_libraries(Demo03-GUI ionGraphics)
target_link_libraries(Demo03-GUI ionWindow)
target_link_libraries(Demo03-GUI ionFramework)
ExecutableDependencies(Demo03-GUI)
add_custom_command(
	TARGET Demo03-GUI POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/OpenSans.ttf $<TARGET_FILE_DIR:Demo03-GUI>)
