#include "shader_to_video.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "screen_quad.h"
#include "shader_program.h"

#include <string>
#include <iostream>

static auto VERTEX_SHADER_CODE {R"(
  #version 460 core
  layout (location = 0) in vec3 aPos;

  void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  }
)"};

ShaderToVideo::ShaderToVideo()
: window{std::make_unique<Window>()} {
  this->InitGLAD();
}

ShaderToVideo::~ShaderToVideo() {
  glfwTerminate();
}

void ShaderToVideo::StartDrawLoop(const char *fragmentShaderBodyCode) {
  Shader vertexShader{ GL_VERTEX_SHADER, VERTEX_SHADER_CODE };

  std::string fragmentShaderHeaderCode {R"(
    #version 460 core
    out vec4 fragColor;
  )"};

  const char *fragmentShaderCode = (
    fragmentShaderHeaderCode + fragmentShaderBodyCode
  ).c_str();

  Shader fragmentShader{ GL_FRAGMENT_SHADER, fragmentShaderCode };

  ShaderProgram shaderProgram{ vertexShader.GetID(), fragmentShader.GetID() };
  
  ScreenQuad screenQuad;

  this->window->StartDrawLoop([&]() {
    // Clear framebuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw screen quad
    shaderProgram.Use();
    screenQuad.Draw();
  });  
}

void ShaderToVideo::InitGLAD() const {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    exit(-1);
  }
}