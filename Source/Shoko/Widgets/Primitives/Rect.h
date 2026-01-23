#pragma once

#include "Widgets/Widget.h"
#include "Renderer.h"

namespace Shoko
{
    class SRect : public SWidget<SRect>
    {
        SHOKO_GENERATED_BODY(SRect)
        
    public:        
        constexpr SRect() = default;
        
        constexpr SRect& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        void Render() const
        {
            FShokoRenderer::DrawRect(Geometry.Location, Geometry.Size, Color);
        }

        constexpr const FWidgetBase* HitTest(FLocation InMouseLocation) const { return nullptr;  }
        
    protected:
        FColor Color = FColor(0, 0, 0, 0);
    };
}
