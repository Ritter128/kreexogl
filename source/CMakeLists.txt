cmake_minimum_required(VERSION 3.23.2)

project(KREEX)

add_executable(${PROJECT_NAME} 
  main.cpp 
)

add_subdirectory(lib/GLFW/)

target_include_directories(${PROJECT_NAME}
  PUBLIC lib/GLFW/include
)

target_link_directories(${PROJECT_NAME} 
  PRIVATE lib/GLFW/src
)

target_link_libraries(${PROJECT_NAME} glfw)