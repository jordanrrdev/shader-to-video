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

    uniform float iTime;
    uniform uint iFrame;
    uniform vec2 iResolution;

    vec2 fragCoord = gl_FragCoord.xy;
  )"};

  fragmentShaderHeaderCode += fragmentShaderBodyCode;

  const char *fragmentShaderCode{ fragmentShaderHeaderCode.c_str() };

  Shader fragmentShader{ GL_FRAGMENT_SHADER, fragmentShaderCode };

  ShaderProgram shaderProgram{ vertexShader.GetID(), fragmentShader.GetID() };
  
  ScreenQuad screenQuad;

  unsigned frame{ 0 };

  this->window->StartDrawLoop([&]() {
    // Clear framebuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SetupUniforms(shaderProgram, frame);

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

void ShaderToVideo::SetupUniforms(const ShaderProgram& shaderProgram, unsigned frame) const {
  shaderProgram.Use();

  auto timeLocation{ shaderProgram.GetUniformLocation("iTime") };
  glUniform1f(timeLocation, float(glfwGetTime()));

  auto frameLocation{ shaderProgram.GetUniformLocation("iFrame") };
  glUniform1ui(frameLocation, frame);

  static bool isStaticUniformsSetup{ false };

  if (!isStaticUniformsSetup) {
    isStaticUniformsSetup = true;

    auto resolutionLocation{ shaderProgram.GetUniformLocation("iResolution") };
    auto [width, height]{ this->window->GetSize() };
    glUniform2f(resolutionLocation, float(width), float(height));
  }
}