#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../../Types/Geometry.h"
#include "../../../Types/Color.h"

namespace Shoko
{
    class FShokoOpenGLRenderer
    {
    public:
        static bool Initialize();
        static void Deinitialize();

        static bool MainLoop();
        static void PreRender();
        static void PostRender();

        static void DrawRect(FGeometry Geometry, FColor Color);
        
        static GLuint CreateGLSLProgram(const char* VertexSource, const char* FragmentSource);

    private:
        static GLFWwindow* Window;

        static GLuint VAO;
        static GLuint VBO;
        static GLuint EBO;
        
        static GLuint RectShader;

        static void SetupQuad();
        static void SetupShaders();
    };

    using FShokoRenderer = FShokoOpenGLRenderer;
}
