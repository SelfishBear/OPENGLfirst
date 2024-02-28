cmake_minimum_required(VERSION 3.27)
project(OpenGLtest)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenGLtest main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/External/glew/include)
add_subdirectory(External/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(External/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

add_subdirectory(External/glew/build/cmake ${CMAKE_CURRENT_BINARY_DIR}/glew)
target_link_libraries(${PROJECT_NAME} PRIVATE glew)

add_subdirectory(External/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)



