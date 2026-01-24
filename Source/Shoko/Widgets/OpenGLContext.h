#pragma once

#include "Widget.h"

namespace Shoko
{
    class SOpenGLContext : public SWidget<SOpenGLContext>
    {
        SHOKO_GENERATED_BODY(SOpenGLContext)

    public:
        
#if SHOKO_RENDERER == SHOKO_RENDERER_OpenGL
        constexpr SOpenGLContext& SetShader(GLuint InShaderProgram)
        {
            ShaderProgram = InShaderProgram;
            TimeUniform = glGetUniformLocation(ShaderProgram, "time");
            return *this;
        }

        constexpr void Render() const
        {
            if(!ShaderProgram) return;

            glUseProgram(ShaderProgram);
            // if (TimeUniform >= 0) glUniform1f(TimeUniform, t);

            glBegin(GL_QUADS);
            glVertex2i(GetGeometry().Location.X, GetGeometry().Location.Y);
            glVertex2i(GetGeometry().Location.X + GetGeometry().Size.X, GetGeometry().Location.Y);
            glVertex2i(GetGeometry().Location.X + GetGeometry().Size.X, GetGeometry().Location.Y + GetGeometry().Size.Y);
            glVertex2i(GetGeometry().Location.X, GetGeometry().Location.Y + GetGeometry().Size.Y);
            glEnd();

            glUseProgram(0);
        }

    private:
        GLuint ShaderProgram = 0;
        GLint TimeUniform = -1;

#else
        void Render() const
        {
            FShokoRenderer::DrawRect(GetGeometry().Location, GetGeometry().Size, FColor::Error);
        }
#endif
    };
}
