#pragma once

#include "Widget.h"
#include "Renderer.h"

namespace Shoko
{
    class SRoundBox : public SWidget<SRoundBox>
    {
        SHOKO_GENERATED_BODY(SRoundBox)
        
    public:        
        constexpr SRoundBox() = default;
        
        constexpr SRoundBox& SetRadius(uint8 InRadius)
        {
            Radius = InRadius;
            return *this;
        }
        
        constexpr SRoundBox& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        void Render() const
        {
            FShokoRenderer::DrawRoundedRect(Geometry.Location, Geometry.Size, Radius, Color);
        }
        
    protected:
        uint8 Radius = 0;
        FColor Color = FColor(0, 0, 0, 0);
    };
}
