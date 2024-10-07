#ifndef __SHADER_TO_VIDEO_WINDOW_GUARD__
#define __SHADER_TO_VIDEO_WINDOW_GUARD__

#include <functional>

#include <GLFW/glfw3.h>

struct WindowSize {
  int width;
  int height;
};

class Window {
public:
  Window();
  ~Window();

  void StartDrawLoop(const std::function<void(void)>& draw) const;

  WindowSize GetSize() const;

private:
  GLFWwindow *glfwWindow;
};

#endif