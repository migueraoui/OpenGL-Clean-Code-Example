#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
// 

const GLuint WIDTH = 800, HEIGHT = 600;

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    GLuint Program;
private:
    GLuint compileShader(const char* source, GLenum type);
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    linkProgram(vertexShader, fragmentShader);
}

GLuint Shader::compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "shader compilation error : " << infoLog << std::endl;
    }
    return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    Program = glCreateProgram();
    glAttachShader(Program, vertexShader);
    glAttachShader(Program, fragmentShader);
    glLinkProgram(Program);
    GLint success;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(Program, 512, nullptr, infoLog);
        std::cerr << "program linking eror: " << infoLog << std::endl;
    }
}

class Renderer {
public:
    void init();
    void render(GLuint VAO, Shader& shader);
    void cleanup(GLuint VAO, GLuint VBO);
};

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::render(GLuint VAO, Shader& shader) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Program;
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::cleanup(GLuint VAO, GLuint VBO) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

class Application {
public:
    Application();
    void run();
private:
    GLFWwindow* window;
    GLuint VAO, VBO;
    Shader shader;
    Renderer renderer;
    void initGLFW();
    void initGLEW();
    void createTriangle();
    void createWindow();
};

Application::Application() 
    : shader("vertex_shader.glsl", "fragment_shader.glsl") {}

void Application::run() {
    initGLFW();
    createWindow();
    initGLEW();
    renderer.init();
    createTriangle();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        renderer.render(VAO, shader);
        glfwSwapBuffers(window);
    }

    renderer.cleanup(VAO, VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Application::initGLEW() {
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Application::createTriangle() {
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Application::createWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(WIDTH, HEIGHT, "openGL clean code", nullptr, nullptr);
    if (!window) {
        std::cerr << "window creation failed!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

int main() {
    Application app;
    app.run();
    return 0;
}
