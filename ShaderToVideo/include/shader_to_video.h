#ifndef __SHADER_TO_VIDEO_GUARD__
#define __SHADER_TO_VIDEO_GUARD__

#define GLFW_INCLUDE_NONE

#include <memory>

#include <glad/glad.h>

#include "window.h"

class ShaderProgram;

class ShaderToVideo {
public:
  ShaderToVideo();
  ~ShaderToVideo();

  void StartDrawLoop(const char *fragmentShaderBodyCode);
private:
  std::unique_ptr<Window> window;

  void InitGLAD() const;

  void SetupUniforms(const ShaderProgram& shaderProgram, unsigned frame) const;
};

#endif