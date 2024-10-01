#ifndef __SHADER_TO_VIDEO_SHADER_PROGRAM_GUARD__
#define __SHADER_TO_VIDEO_SHADER_PROGRAM_GUARD__

#include <initializer_list>

#include <glad/glad.h>

class ShaderProgram{
public:
  ShaderProgram(std::initializer_list<GLuint> shadersIDs);
  ~ShaderProgram();

  void Use() const;

private:
  GLuint id;
};

#endif