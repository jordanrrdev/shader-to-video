#include "shader.h"

#include <iostream>

Shader::Shader(GLenum type, const char *&code)
: id{0} {
  unsigned int shaderID{ glCreateShader(type) };
  
  glShaderSource(shaderID, 1, &code, nullptr);
  glCompileShader(shaderID);

  int success;
  char infoLog[512];
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    exit(-1);
  }

  this->id = shaderID;
}

Shader::~Shader() {
  glDeleteShader(this->id);
}

GLuint Shader::GetID() const {
  return this->id;
}