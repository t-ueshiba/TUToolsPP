project(pair)

file(GLOB sources *.cc)
add_executable(${PROJECT_NAME} ${sources})
