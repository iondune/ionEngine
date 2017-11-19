file(GLOB SOURCES *.cpp)
add_library(ionGUI ${SOURCES})
target_compile_definitions(ionGUI PRIVATE -DION_PROJECT_BASE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/")
