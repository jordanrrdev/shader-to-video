#include "shader_program.h"

#include <glad/glad.h>

#include <iostream>

ShaderProgram::ShaderProgram(std::initializer_list<GLuint> shadersIDs)
: id{0} {
  auto shaderProgram{ glCreateProgram() };

  for (auto it{ shadersIDs.begin() }; it != shadersIDs.end(); ++it)
    glAttachShader(shaderProgram, *it);

  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    exit(-1);
  }

  this->id = shaderProgram;
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(this->id);
}

void ShaderProgram::Use() const {
  glUseProgram(this->id);
}

GLint ShaderProgram::GetUniformLocation(const char* variableName) const {
  return glGetUniformLocation(this->id, variableName);
}