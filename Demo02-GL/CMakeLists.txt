set(TARGET_NAME Demo02-GL)
add_executable(${TARGET_NAME} DemoGL.cpp)

BuildProperties(${TARGET_NAME})
target_link_libraries(${TARGET_NAME} ionGraphicsGL)
target_link_libraries(${TARGET_NAME} ionGraphics)
target_link_libraries(${TARGET_NAME} ionWindow)
target_link_libraries(${TARGET_NAME} ionCore)
ExecutableProperties(${TARGET_NAME})
