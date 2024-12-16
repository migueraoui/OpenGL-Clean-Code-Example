# OpenGL Clean Code Example

a simple OpenGL example written in C++ that demonstrates clean coding practices and modular design. The program creates a triangle with colored vertices and renders it in an OpenGL window using GLFW and GLEW.

## Project Structure

- `main.cpp`: Main program that initializes OpenGL, creates a window, and renders the triangle.
- `Shader.cpp` and `Shader.h`: Classes responsible for shader compilation and linking.
- `Renderer.cpp` and `Renderer.h`: handles OpenGL rendering and clearing operations.
- `Application.cpp` and `Application.h`: manages the application lifecycle and coordinates other classes.

## Requirements

- **OpenGL**: for rendering graphics.
- **GLFW**: for creating windows and handling user input.
- **GLEW**: for managing OpenGL extensions.
- A a++ compiler supporting C++11 or higher.

### How to Compile and Run

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/OpenGL-Clean-Code-Example.git
   cd OpenGL-Clean-Code-Example

## Code Explanation
- Shader Class manages shader compilation and program linking.
- Renderer Class: handles the initialization and rendering of OpenGL objects.
- Application Class: controls the window and openGL context, and main loop.
