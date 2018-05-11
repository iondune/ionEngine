set(TARGET_NAME TestDeployment)
add_executable(${TARGET_NAME} DeploymentTest.cpp glad.cpp)
BuildProperties(TestDeployment)
ExecutableProperties(TestDeployment)

target_link_libraries(${TARGET_NAME} ionCore)
