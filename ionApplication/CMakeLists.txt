file(GLOB SOURCES *.cpp)
add_library(ionApplication ${SOURCES})
target_compile_definitions(ionApplication PRIVATE -DION_PROJECT_BASE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
