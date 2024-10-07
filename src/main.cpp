#include "shader_to_video.h"

int main(int argc, char const *argv[]) {
  auto app = ShaderToVideo();

  auto fragmentShaderCode {R"(
    void main() {
      fragColor = vec4(fragCoord / iResolution, (sin(iTime) + 1.0f) * 0.5f, 1.0f);
    }
  )"};

  app.StartDrawLoop(fragmentShaderCode);
  
  return 0;
}