#BasicOpenGLRenderer
BasicOpenGLRenderer is a C++ rendering engine and application framework built from scratch. This project serves as a sandbox for learning modern OpenGL rendering techniques, exploring C++ application architecture, and mastering C++23 standards.

While the primary focus is 3D rendering, the project also implements a core engine architecture featuring an Application layer, a Layer Stack, and a robust Event system.

## Project Goals
Learning: Deepen understanding of the graphics pipeline and memory management.

Architecture: Implement clean design patterns (Application, Layers, Events).

Refactoring: Continuously improve and modernize code snippets gathered from various educational resources.

## Tech Stack
Language: C++23

Build System: CMake (3.15+)

Graphics API: OpenGL

Windowing & Input: GLFW

Extension Loading: GLEW

Math: GLM

Image Loading: stb_image

## Architecture
The engine is built on a modular architecture to separate the core application logic from the rendering pipeline:

Application: The entry point managing the main loop.

Layer System: A stack of layers allowing modular updates and event handling (similar to standard Game Engine architectures).

Event System: A custom propagation system for Window, Mouse, and Key events.

Renderer: Abstractions for Vertex Arrays, Buffers, Shaders, and Textures.

## Roadmap & Future Features
This is a living project, and the following features are planned for implementation:

[ ] Renderer Abstraction: Create a hardware-agnostic Rendering API to switch between raw OpenGL and a custom software renderer.

[ ] Demo Project: A space simulation (Solar System or Black Hole visualization) to stress-test the engine.

[ ] Physics Engine: Implementation of basic 2D and 3D physics solvers.

[ ] Scene Graph: Basic entity management system.

## Building the Project
The project is designed to be cross-platform (Linux/Windows).

### Prerequisites
Ensure you have a C++ compiler capable of supporting C++23 (e.g., GCC 11+, Clang 14+, MSVC 19.30+).

You will need the following libraries installed on your system or accessible via CMake:

GLFW3

GLEW

GLM

### Linux (Debian/Ubuntu)
You can install the necessary dependencies via the terminal:

Bash

sudo apt-get update
sudo apt-get install build-essential cmake libgl1-mesa-dev libglew-dev libglfw3-dev libglm-dev
Build Instructions
Clone the repository:

Bash

git clone https://github.com/your-username/BasicOpenGLRenderer.git
cd BasicOpenGLRenderer
Generate project files:

Bash

mkdir build
cd build
cmake ..
Compile:

Bash

cmake --build .
Run:

### Linux: ./BasicOpenGLRenderer

### Windows: .\Debug\BasicOpenGLRenderer.exe

## Project Structure
Plaintext

BasicOpenGLRenderer/
├── CMakeLists.txt       # Main build configuration
├── dependencies.cmake   # Dependency linkage
├── src/                 # Source code
│   ├── Core/            # Application, Window, Layer, Events
│   ├── Renderer/        # OpenGL abstractions (Buffers, Shaders)
│   └── main.cpp         # Entry point
└── vendor/              # Third-party libraries (stb_image, etc.)
## License & Credits
This project is for educational purposes. Some code patterns may be derived from various online tutorials and resources (e.g., The Cherno, LearnOpenGL) and adapted/refactored for this specific architecture.
