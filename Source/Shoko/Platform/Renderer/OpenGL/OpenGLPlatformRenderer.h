#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Aliases.h"
#include "Types/Color.h"
#include "Types/StaticArray.h"
#include "Types/Renderer.h"
#include "Types/Vector2D.h"
#include "Types/Angle.h"

namespace Shoko
{
    class FShokoOpenGLPlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    public:
        static GLFWwindow* Window;
        static int WindowWidth;
        static int WindowHeight;
        
        static void UpdateProjection();
        
        static uint32 CompileShader(const char* Source);
        static void DrawRectShader(FLocation TopLeft, FSize Size, uint32 Shader);
        
    private:
        enum class EShaderProgram : uint8
        {
            Default,
            Rect,
            Circle,
            Arc,

            Max
        };
        
        static uint32 ShaderPrograms[static_cast<uint8>(EShaderProgram::Max)];
        static uint32 VAO;
        static uint32 VBO;
        static float Projection[16];
        
    private:
        static void UseShader(EShaderProgram Primitive);
        static void BakeQuad(FLocation TopLeft, FSize Size);
        static void PushQuad();
    };
    
#pragma region Polygon
    template <uint8 N> 
    void FShokoOpenGLPlatformRenderer::DrawPath(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness)
    {
        
    }  
#pragma endregion
    
#pragma region Path
    template <uint8 N>
    void FShokoOpenGLPlatformRenderer::DrawPolygonBorder(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
    {
        
    }
#pragma endregion
    
    using FShokoPlatformRenderer = FShokoOpenGLPlatformRenderer;
}
