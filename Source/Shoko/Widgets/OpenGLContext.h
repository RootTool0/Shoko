#pragma once

#include "Base/Widget.h"

namespace Shoko
{
    SHOKO_CLASS(SOpenGLContext)
    class SOpenGLContext : public SWidget<SOpenGLContext>
    {
        SHOKO_GENERATED_BODY(SOpenGLContext)
		using Super = SWidget<SOpenGLContext>;
        
    public:
        
        void SetShaderProgram(uint32 InShaderProgram) const
        {
            ShaderProgram = InShaderProgram;
        }
        
        void Render() const
        {
#ifdef SHOKO_PLATFORM_USE_OpenGL
            FShokoRenderer::DrawRectShader(GetGeometry().Location, GetGeometry().Size, ShaderProgram);
#else
            FShokoRenderer::DrawRect(GetGeometry().Location, GetGeometry().Size, FColor::Error);
#endif
        }
        
    private:
        mutable uint32 ShaderProgram = 0;
    };
}
