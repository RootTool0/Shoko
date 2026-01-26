// ReSharper disable CppCStyleCast
// ReSharper disable CppZeroConstantCanBeReplacedWithNullptr
// ReSharper disable CppClangTidyPerformanceNoIntToPtr
// ReSharper disable CppClangTidyClangDiagnosticCastFunctionTypeStrict
#include "OpenGLPlatformRenderer.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace Shoko;

#pragma region Private
#define COLOR_2_FLOAT(Color) \
    static_cast<float>((Color).R) / 255.f, \
    static_cast<float>((Color).G) / 255.f, \
    static_cast<float>((Color).B) / 255.f, \
    static_cast<float>((Color).A) / 255.f

std::string LoadShaderSource(const char* Path)
{
    std::ifstream file(Path);
    if(!file.is_open())
    {
        std::cerr << "Failed to open shader: " << Path << "\n";
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

uint32 CompileShader(uint32 Type, const std::string& Source)
{
    uint32 Shader = glCreateShader(Type);
    const char* Src = Source.c_str();
    glShaderSource(Shader, 1, &Src, nullptr);
    glCompileShader(Shader);

    int success;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char InfoLog[512];
        glGetShaderInfoLog(Shader, 512, nullptr, InfoLog);
        std::cerr << "Shader compilation failed:\n" << InfoLog << "\n";
    }
    return Shader;
}

uint32 CreateShaderProgram(const char* ShaderName)
{
    std::string Path = std::string("Source/Shoko/Platform/Renderer/OpenGL/Shaders/") + ShaderName;
    
    uint32 VertexShader   = CompileShader(GL_VERTEX_SHADER,   LoadShaderSource("Source/Shoko/Platform/Renderer/OpenGL/Shaders/Default.vert"));
    uint32 FragmentShader = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSource((Path + ".frag").c_str()));
    
    uint32 Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);
    
    int success;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if(!success)
    {
        char InfoLog[512];
        glGetProgramInfoLog(Program, 512, nullptr, InfoLog);
        std::cerr << "Shader linking failed:\n" << InfoLog << "\n";
    }
    
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    
    return Program;
}

void CalculateBorderRadii(float Radius, float Thickness, EShokoRendererBorderType Type, float& OutInner, float& OutOuter)
{
    switch(Type)
    {
    case EShokoRendererBorderType::Inside:
        OutInner = Radius - Thickness;
        OutOuter = Radius;
        break;
    case EShokoRendererBorderType::Outside:
        OutInner = Radius;
        OutOuter = Radius + Thickness;
        break;
    case EShokoRendererBorderType::Both:
        OutInner = Radius - Thickness * 0.5f;
        OutOuter = Radius + Thickness * 0.5f;
        break;
    }
}
#pragma endregion

int FShokoOpenGLPlatformRenderer::WindowWidth  = 800;
int FShokoOpenGLPlatformRenderer::WindowHeight = 600;
GLFWwindow* FShokoPlatformRenderer::Window = nullptr;

uint32 FShokoPlatformRenderer::ShaderPrograms[static_cast<uint8>(EShaderProgram::Max)];
uint32 FShokoPlatformRenderer::VAO;
uint32 FShokoPlatformRenderer::VBO;
float FShokoPlatformRenderer::Projection[16];

#pragma region Init
bool FShokoOpenGLPlatformRenderer::Initialize()
{
    if(!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }
    
    ShaderPrograms[static_cast<uint8>(EShaderProgram::Default)] = CreateShaderProgram("Default");
    ShaderPrograms[static_cast<uint8>(EShaderProgram::Rect)]    = CreateShaderProgram("Rect/Rect");
    ShaderPrograms[static_cast<uint8>(EShaderProgram::Circle)]  = CreateShaderProgram("Circle/Circle");
    ShaderPrograms[static_cast<uint8>(EShaderProgram::Arc)]     = CreateShaderProgram("Arc/Arc");
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    UpdateProjection();
    
    return true;
}

void FShokoOpenGLPlatformRenderer::Deinitialize()
{
    for(unsigned int& ShaderProgram : ShaderPrograms)
    {
        glDeleteProgram(ShaderProgram);
        ShaderProgram = 0;
    }

    if(VBO) glDeleteBuffers(1, &VBO);
    if(VAO) glDeleteVertexArrays(1, &VAO);
}

void FShokoOpenGLPlatformRenderer::PreRender() {}
void FShokoOpenGLPlatformRenderer::PostRender()
{
    if(Window) glfwSwapBuffers(Window);
}
#pragma endregion

#pragma region Base (3 / 3)
void FShokoOpenGLPlatformRenderer::Fill(FColor Color)
{
    glClearColor(COLOR_2_FLOAT(Color));
    glClear(GL_COLOR_BUFFER_BIT);
}
void FShokoOpenGLPlatformRenderer::DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness)
{
    UseShader(EShaderProgram::Rect);
    
    float vertices[] =
    {
        static_cast<float>(Start.X), static_cast<float>(Start.Y), 0.0f, 0.0f,
        static_cast<float>(End.X),   static_cast<float>(End.Y),   1.0f, 1.0f,
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    
    glUniform4f(glGetUniformLocation(ShaderPrograms[static_cast<uint8>(EShaderProgram::Rect)], "uColor"), COLOR_2_FLOAT(Color));
    
    glLineWidth(static_cast<float>(Thickness));
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}
void FShokoOpenGLPlatformRenderer::DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    UseShader(EShaderProgram::Arc);

    float inner, outer;
    CalculateBorderRadii((float)Radius, (float)BorderThickness, BorderType, inner, outer);
    
    FLocation topLeft = Center - static_cast<int16>(outer);
    FSize size = FSize(static_cast<uint16>(outer * 2));
    
    BakeQuad(topLeft, size);

    uint32 Shader = ShaderPrograms[static_cast<uint8>(EShaderProgram::Arc)];
    
    glUniform4f(glGetUniformLocation(Shader, "uColor"), COLOR_2_FLOAT(Color));
    glUniform1f(glGetUniformLocation(Shader, "uStartAngle"), StartAngle.GetRadians());
    glUniform1f(glGetUniformLocation(Shader, "uEndAngle"),   EndAngle.GetRadians());
    glUniform1f(glGetUniformLocation(Shader, "uInnerRadius"), inner / outer);
    glUniform2f(glGetUniformLocation(Shader, "uSize"), (float)size.X, (float)size.Y);

    PushQuad();
}
#pragma endregion

#pragma region Rect (2 / 2)
void FShokoOpenGLPlatformRenderer::DrawRect(FLocation TopLeft, FSize Size, FColor Color)
{
    DrawRoundedRectBorder(TopLeft, Size, 0, Color, 0, EShokoRendererBorderType::Inside);
}
void FShokoOpenGLPlatformRenderer::DrawRectBorder(FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    DrawRoundedRectBorder(TopLeft, Size, 0, Color, BorderThickness, BorderType);
}
#pragma endregion

#pragma region Rounded Rect (2 / 2)
void FShokoOpenGLPlatformRenderer::DrawRoundedRect(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color)
{
    DrawRoundedRectBorder(TopLeft, Size, CornerRadius, Color, 0, EShokoRendererBorderType::Inside);
}
void FShokoOpenGLPlatformRenderer::DrawRoundedRectBorder(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    UseShader(EShaderProgram::Rect);

    if(BorderType == EShokoRendererBorderType::Outside)
    {
        TopLeft -= BorderThickness;
        Size    += BorderThickness * 2;
    }
    else if (BorderType == EShokoRendererBorderType::Both)
    {
        TopLeft -= static_cast<int16>(BorderThickness / 2);
        Size    += BorderThickness;
    }
    
    BakeQuad(TopLeft, Size);
    
    uint32 Shader = ShaderPrograms[static_cast<uint8>(EShaderProgram::Rect)];
    glUniform4f(glGetUniformLocation(Shader, "uColor"), COLOR_2_FLOAT(Color));
    glUniform2f(glGetUniformLocation(Shader, "uSize"), (float)Size.X, (float)Size.Y);
    glUniform1f(glGetUniformLocation(Shader, "uRadius"), (float)CornerRadius);
    glUniform1f(glGetUniformLocation(Shader, "uThickness"), (float)BorderThickness);
    
    PushQuad();
}
#pragma endregion

#pragma region Circle (2 / 2)
void FShokoOpenGLPlatformRenderer::DrawCircle(FLocation Center, uint8 Radius, FColor Color)
{
    DrawEllipse(Center, FSize(Radius * 2), Color);
}
void FShokoOpenGLPlatformRenderer::DrawCircleBorder(FLocation Center, uint8 Radius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    DrawEllipseBorder(Center, FSize(Radius * 2), Color, BorderThickness, BorderType);
}
#pragma endregion

#pragma region Ellipse (2 / 2)
void FShokoOpenGLPlatformRenderer::DrawEllipse(FLocation Center, FSize Size, FColor Color)
{
    DrawEllipseBorder(Center, Size, Color, 0, EShokoRendererBorderType::Inside);
}
void FShokoOpenGLPlatformRenderer::DrawEllipseBorder(FLocation Center, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    UseShader(EShaderProgram::Circle);
    
    if(BorderType == EShokoRendererBorderType::Outside)
    {
        Size.X += BorderThickness * 2;
        Size.Y += BorderThickness * 2;
    }
    else if (BorderType == EShokoRendererBorderType::Both)
    {
        Size.X += BorderThickness;
        Size.Y += BorderThickness;
    }
    
    BakeQuad(Center - (Size / 2), Size);
    
    glUniform4f(glGetUniformLocation(ShaderPrograms[static_cast<uint8>(EShaderProgram::Circle)], "uColor"), COLOR_2_FLOAT(Color));
    glUniform2f(glGetUniformLocation(ShaderPrograms[static_cast<uint8>(EShaderProgram::Circle)], "uSize"), (float)Size.X, (float)Size.Y);
    glUniform1f(glGetUniformLocation(ShaderPrograms[static_cast<uint8>(EShaderProgram::Circle)], "uThickness"), (float)BorderThickness);
    
    PushQuad();
}
#pragma endregion

#pragma region Circle Sector (2 / 2)
void FShokoOpenGLPlatformRenderer::DrawCircleSector(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color)
{
    DrawCircleSectorBorder(Center, Radius, StartAngle, EndAngle, Color, Radius, EShokoRendererBorderType::Inside);
}
void FShokoOpenGLPlatformRenderer::DrawCircleSectorBorder(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    UseShader(EShaderProgram::Arc);
    
    float inner, outer;
    CalculateBorderRadii((float)Radius, (float)BorderThickness, BorderType, inner, outer);

    BakeQuad(Center - (int16)outer, FSize((uint16)outer * 2));

    uint32 Shader = ShaderPrograms[static_cast<uint8>(EShaderProgram::Arc)];
    glUniform4f(glGetUniformLocation(Shader, "uColor"), COLOR_2_FLOAT(Color));
    glUniform1f(glGetUniformLocation(Shader, "uStartAngle"), StartAngle.GetRadians());
    glUniform1f(glGetUniformLocation(Shader, "uEndAngle"), EndAngle.GetRadians());
    glUniform1f(glGetUniformLocation(Shader, "uInnerRadius"), inner / outer);

    PushQuad();
}
#pragma endregion

#pragma region Bezier (0 / 2)
void FShokoOpenGLPlatformRenderer::DrawQuadraticBezier(FLocation A, FLocation B, FLocation C, FColor Color) {}
void FShokoOpenGLPlatformRenderer::DrawCubicBezier(FLocation A, FLocation B, FLocation C, FLocation D, FColor Color) {}
#pragma endregion

#pragma region Text (0 / 1)
void FShokoOpenGLPlatformRenderer::DrawText(FLocation Center, const char* Text, uint16 Len, uint8 Size, FColor Color, bool bCentered) {}
#pragma endregion

#pragma region Private
void FShokoOpenGLPlatformRenderer::UseShader(EShaderProgram Primitive)
{
    uint32 Shader = ShaderPrograms[static_cast<uint8>(Primitive)];
    glUseProgram(Shader);
    
    int loc = glGetUniformLocation(Shader, "uProjection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, Projection);
}

void FShokoOpenGLPlatformRenderer::UpdateProjection()
{
    glViewport(0, 0, WindowWidth, WindowHeight);
    
    float left   = 0.0f;
    float right  = static_cast<float>(WindowWidth);
    float top    = 0.0f;
    float bottom = static_cast<float>(WindowHeight);
    float nearZ  = -1.0f;
    float farZ   = 1.0f;
    
    Projection[0]  = 2.0f / (right - left); Projection[4]  = 0.0f;                  Projection[8]  = 0.0f;                   Projection[12] = -(right + left) / (right - left);
    Projection[1]  = 0.0f;                  Projection[5]  = 2.0f / (top - bottom); Projection[9]  = 0.0f;                   Projection[13] = -(top + bottom) / (top - bottom);
    Projection[2]  = 0.0f;                  Projection[6]  = 0.0f;                  Projection[10] = -2.0f / (farZ - nearZ); Projection[14] = -(farZ + nearZ) / (farZ - nearZ);
    Projection[3]  = 0.0f;                  Projection[7]  = 0.0f;                  Projection[11] = 0.0f;                   Projection[15] = 1.0f;
}

void FShokoOpenGLPlatformRenderer::BakeQuad(FLocation TopLeft, FSize Size)
{
    float x0 = static_cast<float>(TopLeft.X);
    float y0 = static_cast<float>(TopLeft.Y);
    float x1 = x0 + static_cast<float>(Size.X);
    float y1 = y0 + static_cast<float>(Size.Y);
    
    float vertices[6 * 4] = {
        x0, y0, 0.0f, 0.0f,  // TL
        x1, y0, 1.0f, 0.0f,  // TR
        x1, y1, 1.0f, 1.0f,  // BR

        x0, y0, 0.0f, 0.0f,  // TL
        x1, y1, 1.0f, 1.0f,  // BR
        x0, y1, 0.0f, 1.0f   // BL
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void FShokoOpenGLPlatformRenderer::PushQuad()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
#pragma endregion
