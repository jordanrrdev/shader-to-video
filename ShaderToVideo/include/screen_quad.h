#ifndef __SHADER_TO_VIDEO_SCREEN_QUAD_GUARD__
#define __SHADER_TO_VIDEO_SCREEN_QUAD_GUARD__

#include <glad/glad.h>

class ScreenQuad {
public:
  ScreenQuad();
  ~ScreenQuad();

  void Draw() const;

private:
  GLuint vao;
  GLuint vbo;
};

#endif