#include "screen_quad.h"

ScreenQuad::ScreenQuad()
: vao{0}
, vbo{0} {
  // Set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] {
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f
  }; 

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind the Vertex Array Object first, then bind and set vertex buffer(s),
  // and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Note that this is allowed, the call to glVertexAttribPointer registered the VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind.
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  this->vao = vao;
  this->vbo = vbo;
}

ScreenQuad::~ScreenQuad() {
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);
}

void ScreenQuad::Draw() const {
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}