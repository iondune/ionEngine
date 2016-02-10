file(GLOB SOURCES *.cpp)
add_executable(TestUnits ${SOURCES})

# Libraries
target_link_libraries(TestUnits ionScene)
target_link_libraries(TestUnits ionGraphics)
