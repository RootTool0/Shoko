#pragma once

#include "Renderer.h"
#include "Widget.h"
#include "Types/StringView.h"

namespace Shoko
{
    class SText : public SWidget<SText>
    {
        SHOKO_GENERATED_BODY(SText)
        
    public:
        constexpr SText() { Geometry.Size = FSize(0); }
        
        constexpr SText& SetText(FStringView InText)
        {
            Text = InText;
            return *this;
        }

        constexpr SText& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        constexpr SText& SetSize(uint8 InSize)
        {
            Size = InSize;
            return *this;
        }
        
        void Render() const
        {
            if(!Text.IsEmpty()) FShokoRenderer::DrawText(Geometry.Location, Text.GetData(), Text.Len(), Size, Color);
        }
        
    private:
        FStringView Text;
        FColor Color = FColor(255, 255, 255, 255);
        uint8 Size = 20;
    };
}
