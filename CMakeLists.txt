cmake_minimum_required(VERSION 3.30)
project(ShaderToVideo VERSION 0.1 LANGUAGES CXX)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(opengl_system REQUIRED)
find_package(ffmpeg REQUIRED)

add_library(shader_to_video STATIC
  ShaderToVideo/src/shader_to_video.cpp
  ShaderToVideo/src/shader.cpp
  ShaderToVideo/src/shader_program.cpp
  ShaderToVideo/src/screen_quad.cpp
  ShaderToVideo/src/window.cpp
)
target_include_directories(shader_to_video PUBLIC ShaderToVideo/include)
target_link_libraries(shader_to_video
  PUBLIC
    glad::glad
    glfw
  PRIVATE
    opengl::opengl
    ffmpeg::ffmpeg
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  shader_to_video
)