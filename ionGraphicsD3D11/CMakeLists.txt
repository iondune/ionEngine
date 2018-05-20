set(TARGET_NAME ionGraphicsGL)
file(GLOB SOURCES *.cpp)
add_library(${TARGET_NAME} ${SOURCES})
BuildProperties(${TARGET_NAME})
