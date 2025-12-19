# Minecraft Engine - Modular Architecture

## Project Structure Overview

The Minecraft project is now organized into clear, separate modules, each with its own header (.h) and implementation (.cpp) files.

### Core Modules

#### 1. **Window Module** (`window.h` / `window.cpp`)
- **Responsibility**: OpenGL window and context management
- **Key Classes**: `Window`
- **Features**:
  - GLFW window creation and initialization
  - GLEW initialization
  - GL context setup
  - Buffer swap and event polling
  - Input mode configuration
- **Dependencies**: GLFW, GLEW

#### 2. **Input Module** (`input.h` / `input.cpp`)
- **Responsibility**: User input handling (keyboard and mouse)
- **Key Classes**: `InputManager`
- **Features**:
  - Keyboard state polling
  - Mouse position and delta tracking
  - Input sensitivity configuration
  - Abstracted input queries
- **Dependencies**: GLFW, GLM

#### 3. **Camera Module** (`camera.h` / `camera.cpp`)
- **Responsibility**: 3D camera control and view matrix generation
- **Key Classes**: `Camera`
- **Features**:
  - Free-look camera with yaw/pitch control
  - Keyboard-based movement (WASD + Space/Shift)
  - View matrix computation
  - Position, front, and up vector management
- **Dependencies**: GLM

#### 4. **Shader Module** (`shader.h` / `shader.cpp`)
- **Responsibility**: OpenGL shader compilation and management
- **Key Classes**: `Shader`
- **Features**:
  - Vertex and fragment shader compilation
  - Program linking and error checking
  - Uniform variable setting (matrices, etc.)
  - Shader program usage management
- **Dependencies**: GLEW, GLM

#### 5. **Mesh Module** (`mesh.h` / `mesh.cpp`)
- **Responsibility**: 3D mesh data (vertices, indices) and rendering
- **Key Classes**: `CubeMesh`
- **Features**:
  - Cube vertex data definition
  - VAO (Vertex Array Object) and VBO (Vertex Buffer Object) management
  - Draw command execution
- **Dependencies**: GLEW

#### 6. **Buffer Module** (`buffer.h` / `buffer.cpp`)
- **Responsibility**: Generic OpenGL buffer management
- **Key Classes**: `Buffer`
- **Features**:
  - Buffer creation and deletion
  - Buffer data initialization
- **Dependencies**: GLEW

#### 7. **Renderer Module** (`renderer.h` / `renderer.cpp`)
- **Responsibility**: Scene rendering coordination
- **Key Classes**: `Renderer`
- **Features**:
  - Render pipeline management
  - Uniform matrix passing
  - Clear buffer operations
  - Centralized rendering logic
- **Dependencies**: Shader, Mesh, GLM, GLEW

#### 8. **Application Module** (`app.h` / `app.cpp`)
- **Responsibility**: Main application orchestration
- **Key Classes**: `Minecraft`
- **Features**:
  - Module initialization and cleanup
  - Main game loop management
  - Input handling coordination
  - Timing and frame rate control
  - Mouse callback registration and handling
- **Dependencies**: All modules

### Module Dependencies Graph

```
Window <--> Input
    ^          ^
    |          |
    +---> App <------+
           ^         |
           |         |
       Camera    Renderer
         ^         ^  |
         |         |  |
       Shader <----+  |
         |            |
         +---> Mesh   |
                 ^    |
                 |    |
               Buffer-+
```

## Class Responsibilities

### Window
- OpenGL context initialization
- Window lifecycle management
- GL state setup (depth test, clear color)

### InputManager
- GLFW event polling
- Keyboard state queries
- Mouse position and movement tracking

### Camera
- First-person camera implementation
- View matrix calculation
- Movement physics (WASD/Space/Shift)

### Shader
- GLSL compilation
- Program linking
- Uniform variable management

### CubeMesh
- Cube geometry definition
- VAO/VBO lifecycle
- Draw commands

### Renderer
- Render pipeline orchestration
- Matrix transformations
- Clear operations

### Minecraft (Application)
- Module coordination
- Main loop execution
- Callback setup
- Resource cleanup

## Compilation
All modules are compiled together as defined in `CMakeLists.txt`:
```
src/app_new.cpp      (renamed to app.cpp)
src/buffer.cpp
src/camera.cpp
src/input.cpp
src/main.cpp
src/mesh.cpp
src/renderer.cpp
src/shader.cpp
src/window.cpp
```

## Usage Example
```cpp
Minecraft app;
app.run();
```

This will:
1. Initialize all modules
2. Run the main game loop
3. Handle all input and rendering
4. Clean up resources on exit

## Future Extensions
This modular structure allows easy addition of:
- Physics system
- Audio system
- Texture management
- Lighting system
- UI system
- Scene management
- Asset loading
