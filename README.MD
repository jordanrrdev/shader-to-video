# Shader to Video

## Introduction
Shader to Video allows users to generate videos from OpenGL GLSL shaders. The syntax is similar, but simpler to the one used on [ShaderToy](https://www.shadertoy.com/).

## How to install
Clone the current git repository and enter the generated folder in your terminal.

Download the needed packages with Conan:

`conan install . -pr=moderncpp --output-folder=build --build=missing -pr:b=moderncpp`

Choose a CMake preset. List the ones available:
`cmake --list-presets`

Set CMake preset and build preset
`cmake --preset conan-default`
`cmake --build --preset conan-release`

Test the installation by executing `build\build\Release\ShaderToVideo.exe` or `build/build/Release/ShaderToVideo`.

After following the steps above, you can also install the CMake extension on Visual Studio Code and start building and executing from there.