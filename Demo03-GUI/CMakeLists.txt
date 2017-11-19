add_executable(Demo03-GUI DemoGUI.cpp)

target_link_libraries(Demo03-GUI ionGUI)
target_link_libraries(Demo03-GUI ionGraphicsGL)
target_link_libraries(Demo03-GUI ionGraphics)
target_link_libraries(Demo03-GUI ionWindow)
target_link_libraries(Demo03-GUI ionCore)
ExecutableDependencies(Demo03-GUI)
