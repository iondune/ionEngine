set(TARGET_NAME ionCore)
file(GLOB SOURCES *.cpp)
add_library(${TARGET_NAME} ${SOURCES})
BuildProperties(${TARGET_NAME})
