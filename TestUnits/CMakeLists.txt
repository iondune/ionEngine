set(TARGET_NAME TestUnits)
file(GLOB SOURCES *.cpp)
add_executable(${TARGET_NAME} ${SOURCES})
BuildProperties(${TARGET_NAME})

# Libraries
target_link_libraries(${TARGET_NAME} ionScene)
target_link_libraries(${TARGET_NAME} ionGraphics)
target_link_libraries(${TARGET_NAME} ionCore)
