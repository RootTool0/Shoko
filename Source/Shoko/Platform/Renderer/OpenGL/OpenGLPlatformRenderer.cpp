#include "../../../Config.h"
#if SHOKO_RENDERER == SHOKO_RENDERER_OpenGL

#include "OpenGLPlatformRenderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace Shoko;

GLFWwindow* FShokoOpenGLPlatformRenderer::Window = nullptr;

GLuint FShokoOpenGLPlatformRenderer::VAO = 0;
GLuint FShokoOpenGLPlatformRenderer::VBO = 0;
GLuint FShokoOpenGLPlatformRenderer::EBO = 0;

GLuint FShokoOpenGLPlatformRenderer::RectShader = 0;

bool FShokoOpenGLPlatformRenderer::Initialize()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW init failed\n";
        return false;
    }

    // Настройка OpenGL 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Создание окна
    Window = glfwCreateWindow(800, 600, "Hi, Shoko! OpenGL", nullptr, nullptr);
    if (!Window)
    {
        std::cerr << "GLFW window creation failed\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1); // VSync

    // Инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    // Viewport — фиксированный размер окна
    glViewport(0, 0, 800, 600);

    // Ортографическая проекция для 2D UI
    // Projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    SetupQuad();
    SetupShaders();

    return true;
}

void FShokoOpenGLPlatformRenderer::Deinitialize()
{
    if(Window)
    {
        glfwDestroyWindow(Window);
        Window = nullptr;
    }
    glfwTerminate();
}

bool FShokoOpenGLPlatformRenderer::MainLoop()
{
    return !glfwWindowShouldClose(Window);
}

void FShokoOpenGLPlatformRenderer::PreRender()
{
    glClearColor(30.0f/255.0f, 30.0f/255.0f, 120.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void FShokoOpenGLPlatformRenderer::PostRender()
{
    glfwSwapBuffers(Window);
    glfwPollEvents();
}

/*
void FShokoOpenGLPlatformRenderer::DrawRect(FGeometry Geometry, FColor Color)
{
    if (!RectShader) return;

    glUseProgram(RectShader);
    
    float model[16] = {
        static_cast<float>(Geometry.Size.X), 0, 0, 0,
        0, static_cast<float>(Geometry.Size.Y), 0, 0,
        0, 0, 1, 0,
        static_cast<float>(Geometry.Location.X), static_cast<float>(Geometry.Location.Y), 0, 1
    };
    
    float Projection[16] = {
        2.0f / 800.0f, 0, 0, 0,
        0, 2.0f / -600.0f, 0, 0,
        0, 0, -1.0f, 0,
        -1.0f, 1.0f, 0, 1.0f
    };
    
    GLint locModel = glGetUniformLocation(RectShader, "uModel");
    glUniformMatrix4fv(locModel, 1, GL_FALSE, model);

    GLint locProj = glGetUniformLocation(RectShader, "uProjection");
    glUniformMatrix4fv(locProj, 1, GL_FALSE, Projection);

    GLint locColor = glGetUniformLocation(RectShader, "uColor");
    glUniform4f(locColor, Color.GetNormalizedR(), Color.GetNormalizedG(), Color.GetNormalizedB(), Color.GetNormalizedA());

    bool bLol = false;
    glPolygonMode(GL_FRONT_AND_BACK, bLol ? GL_FILL : GL_LINE);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}
*/

/*
void FShokoOpenGLPlatformRenderer::DrawRect(FGeometry Geometry, FColor Color)
{
    float windowWidth = 800;
    float windowHeight = 600;
    
    float x0 = 2.0f * Geometry.Location.X / windowWidth - 1.0f;
    float y0 = 1.0f - 2.0f * Geometry.Location.Y / windowHeight;
    float x1 = 2.0f * (Geometry.Location.X + Geometry.Size.X) / windowWidth - 1.0f;
    float y1 = 1.0f - 2.0f * (Geometry.Location.Y + Geometry.Size.Y) / windowHeight;

    float vertices[] = {
        x0, y0, Color.R, Color.G, Color.B, Color.A,
        x1, y0, Color.R, Color.G, Color.B, Color.A,
        x1, y1, Color.R, Color.G, Color.B, Color.A,
        x0, y1, Color.R, Color.G, Color.B, Color.A
    };

    unsigned int indices[] = { 0,1,2, 2,3,0 };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
*/

void FShokoOpenGLPlatformRenderer::DrawRect(FGeometry Geometry, FColor Color)
{
    if (!RectShader) return;

    glUseProgram(RectShader);

    // Рассчитываем вершины прямоугольника в NDC ([-1,1])
    float x0 = 2.0f * Geometry.Location.X / 800.0f - 1.0f;         // левый
    float y0 = 1.0f - 2.0f * Geometry.Location.Y / 600.0f;         // верхний
    float x1 = 2.0f * (Geometry.Location.X + Geometry.Size.X) / 800.0f - 1.0f;  // правый
    float y1 = 1.0f - 2.0f * (Geometry.Location.Y + Geometry.Size.Y) / 600.0f;  // нижний

    float vertices[] = {
        x0, y0,   // верхний левый
        x1, y0,   // верхний правый
        x1, y1,   // нижний правый
        x0, y1    // нижний левый
    };

    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

    // Загружаем вершины на GPU (динамически)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    // Цвет через uniform, как ты использовал
    GLint locColor = glGetUniformLocation(RectShader, "uColor");
    glUniform4f(locColor,
                Color.GetNormalizedR(),
                Color.GetNormalizedG(),
                Color.GetNormalizedB(),
                Color.GetNormalizedA());

    // Режим каркаса или заливки
    bool bWireframe = false;
    glPolygonMode(GL_FRONT_AND_BACK, bWireframe ? GL_LINE : GL_FILL);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}


GLuint CompileShader(GLenum Type, const char* Source)
{
    GLuint Shader = glCreateShader(Type);
    glShaderSource(Shader, 1, &Source, nullptr);
    glCompileShader(Shader);

    GLint Success = 0;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        char Log[512];
        glGetShaderInfoLog(Shader, 512, nullptr, Log);
        std::cerr << "Shader compile error:\n" << Log << std::endl;
        glDeleteShader(Shader);
        return 0;
    }

    return Shader;
}

GLuint FShokoOpenGLPlatformRenderer::CreateGLSLProgram(const char* VertexSource, const char* FragmentSource)
{
    GLuint VertexShader   = CompileShader(GL_VERTEX_SHADER, VertexSource);
    GLuint FragmentShader = CompileShader(GL_FRAGMENT_SHADER, FragmentSource);

    if (!VertexShader || !FragmentShader)
        return 0;

    GLuint Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    GLint Success = 0;
    glGetProgramiv(Program, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        char Log[512];
        glGetProgramInfoLog(Program, 512, nullptr, Log);
        std::cerr << "Program link error:\n" << Log << std::endl;
        glDeleteProgram(Program);
        Program = 0;
    }

    glDetachShader(Program, VertexShader);
    glDetachShader(Program, FragmentShader);
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    return Program;
}

void FShokoOpenGLPlatformRenderer::SetupQuad()
{
    float Vertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    unsigned int Indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void FShokoOpenGLPlatformRenderer::SetupShaders()
{
    RectShader = CreateGLSLProgram(
        #include "Shaders/Rect.vert"
    ,
        #include "Shaders/Rect.frag"
    );
}

#endif
