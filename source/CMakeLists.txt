cmake_minimum_required(VERSION 3.23.2)

project(KREEX)

add_executable(${PROJECT_NAME} 
  main.cpp 
  KRXApp.cpp KRXWindow.cpp 
  KRXApp.hpp KRXWindow.hpp

  renderer/KRXVertexBuffer.cpp
  renderer/KRXVertexBuffer.hpp
  renderer/KRXIndexBuffer.cpp
  renderer/KRXIndexBuffer.hpp
  debug/debug.cpp
  debug/debug.hpp
)

add_subdirectory(lib/GLFW/)
add_subdirectory(lib/GLAD/)
add_subdirectory(lib/GLM/)

target_include_directories(${PROJECT_NAME}
  PUBLIC lib/GLFW/include/
  PUBLIC lib/GLAD/include/
  PUBLIC lib/GLM/
)

target_link_directories(${PROJECT_NAME} 
  PRIVATE lib/GLFW/src/
  PRIVATE lib/GLAD/src/
)

target_link_libraries(${PROJECT_NAME} glfw glad)