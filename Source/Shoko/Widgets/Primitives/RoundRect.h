#pragma once

#include "Widgets/Widget.h"
#include "Renderer.h"

namespace Shoko
{
    SHOKO_CLASS(SRoundRect)
    class SRoundRect : public SWidget<SRoundRect>
    {
        SHOKO_GENERATED_BODY(SRoundRect)
        
    public:        
        constexpr SRoundRect() = default;
        
        constexpr SRoundRect& SetRadius(uint8 InRadius)
        {
            Radius = InRadius;
            return *this;
        }
        
        constexpr SRoundRect& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        void Render() const
        {
            FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, Color);
        }
        
        constexpr const FWidgetBase* HitTest(FLocation InMouseLocation) const { return nullptr;  }
        
    protected:
        uint8 Radius = 0;
        FColor Color = FColor(0, 0, 0);
    };
}
