#include "window.h"

#include <iostream>

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
static void processInput(GLFWwindow *window);

Window::Window()
: glfwWindow{nullptr} {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window{ glfwCreateWindow(800, 600, "OpenGLToVideo", nullptr, nullptr) };
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(-1);
  }

  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  this->glfwWindow = window;
}

Window::~Window() {
  if (this->glfwWindow)
    glfwDestroyWindow(this->glfwWindow);
}

void Window::StartDrawLoop(const std::function<void(void)>& draw) const {
  auto window{ this->glfwWindow };

  if (!window)
    return;

  while(!glfwWindowShouldClose(window)) {
    processInput(window);

    draw();

    glfwSwapBuffers(window);
    glfwPollEvents();    
  }
}

WindowSize Window::GetSize() const {
  int width, height;
  glfwGetWindowSize(this->glfwWindow, &width, &height);
  return WindowSize{ width, height };
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}