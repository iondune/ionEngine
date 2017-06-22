add_executable(Demo05-Application DemoApplication.cpp)

target_link_libraries(Demo05-Application ionApplication)
target_link_libraries(Demo05-Application ionScene)
target_link_libraries(Demo05-Application ionGraphicsGL)
target_link_libraries(Demo05-Application ionGraphics)
target_link_libraries(Demo05-Application ionWindow)
target_link_libraries(Demo05-Application ionFramework)
target_link_libraries(Demo05-Application ionCore)
ExecutableDependencies(Demo05-Application)
add_custom_command(
	TARGET Demo05-Application POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:Demo05-Application>/Assets)
