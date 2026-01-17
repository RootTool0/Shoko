#pragma once

#include <iostream>

#include "Widget.h"
#include "Renderer.h"

namespace Shoko
{
    class SBoxWidget : public SWidget<SBoxWidget>
    {
        SHOKO_GENERATED_BODY(SBoxWidget)
        
    public:        
        constexpr SBoxWidget() = default;
        
        constexpr SBoxWidget& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        void Render() const
        {
            FShokoRenderer::DrawRect(Geometry, Color);
        }

        void CallOnHover() const { std::cout << "LOL\n"; }
        void CallOnUnhover() const { std::cout << "KEK\n"; }
        
    protected:
        FColor Color = FColor(0, 0, 0, 0);
    };
}
