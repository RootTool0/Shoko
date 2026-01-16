#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Types/Geometry.h"
#include "Types/Color.h"
#include "Types/Vector2D.h"

namespace Shoko
{
    class FShokoOpenGLPlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    public:
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

    using FShokoRenderer = FShokoOpenGLPlatformRenderer;
}
