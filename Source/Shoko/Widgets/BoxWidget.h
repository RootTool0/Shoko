#pragma once

#include "Widget.h"
#include "Renderer.h"

namespace Shoko
{
    class SBox : public SWidget<SBox>
    {
        SHOKO_GENERATED_BODY(SBox)
        
    public:        
        constexpr SBox() = default;
        
        constexpr SBox& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        void Render() const
        {
            FShokoRenderer::DrawRect(Geometry.Location, Geometry.Size, Color);
        }
        
    protected:
        FColor Color = FColor(0, 0, 0, 0);
    };
}
