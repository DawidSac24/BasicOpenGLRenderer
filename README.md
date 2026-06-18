# OpenGLRenderer

A high-performance, modular OpenGL rendering engine built with C++23.

## Features

- **Modern C++23**: Utilizes the latest language features for clean and efficient code.
- **Modular Architecture**: Clear separation between the Engine core and Application layers.
- **Cross-Platform**: Designed to run on Linux and Windows.
- **Robust Build System**: Professional CMake configuration with vcpkg integration and presets.

## Prerequisites

### 1. C++ Compiler
- **Linux**: GCC 13+ or Clang 16+
- **Windows**: MSVC 2022 (v143) or later

### 2. Build Tools
- [CMake](https://cmake.org/download/) (version 3.21 or higher)
- [Ninja](https://ninja-build.org/) (recommended for fast builds)
- [vcpkg](https://vcpkg.io/) (C++ package manager)

### 3. Dependencies (Linux)
Install the following system libraries:
```bash
sudo apt update
sudo apt install -y build-essential tar curl zip unzip pkg-config libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/your-username/OpenGLRenderer.git
cd OpenGLRenderer
```

### 2. Set up vcpkg
Ensure you have `vcpkg` installed and the `VCPKG_ROOT` environment variable set.
```bash
export VCPKG_ROOT=/path/to/your/vcpkg
```

### 3. Build using CMake Presets

#### Linux
```bash
# Configure the project
cmake --preset dev-linux

# Build the project
cmake --build --preset dev-linux
```

#### Windows
```powershell
# Configure the project
cmake --preset dev-win

# Build the project
cmake --build --preset dev-win
```

### 4. Running the Application
The executable will be located in `build/<preset-name>/bin/`.
```bash
./build/dev-linux/bin/OpenGLRenderer
```

## Installation
To install the engine and application to a specific directory:
```bash
cmake --install build/dev-linux --prefix /your/install/path
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
