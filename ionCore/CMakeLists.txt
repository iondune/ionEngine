
# CMake
project(libionCore VERSION ${ION_ENGINE_VERSION} LANGUAGES CXX)

# Sources
file(GLOB SOURCES *.cpp)
add_library(ionCore ${SOURCES})

# Install
install(TARGETS ionCore EXPORT ionCoreConfig
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(EXPORT ionCoreConfig DESTINATION share/ionCore/cmake)
export(TARGETS ionCore FILE ionCoreConfig.cmake)
