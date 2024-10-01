#ifndef __SHADER_TO_VIDEO_SHADER_GUARD__
#define __SHADER_TO_VIDEO_SHADER_GUARD__

#include <glad/glad.h>

class Shader {
public:
  Shader(GLenum type, const char *&code);
  ~Shader();

  GLuint GetID() const;

private:
  GLuint id;
};

#endif