#pragma once

#include "Renderer.h"
#include "Widget.h"
#include "Types/StringView.h"

namespace Shoko
{
    SHOKO_CLASS(SText)
    class SText : public SWidget<SText>
    {
        SHOKO_GENERATED_BODY(SText)

        using Super = SWidget<SText>;
        
    public:
        constexpr SText() { Super::SetSize(FSize(0, 0)); }

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
        
        constexpr SText& SetTextSize(uint8 InSize)
        {
            Size = InSize;
            return *this;
        }
        
        void Render() const
        {
            if(!Text.IsEmpty())
                FShokoRenderer::DrawText(GetGeometry().Location, Text.GetData(), Text.Len(), Size, Color, true);
        }
        
    private:
        FStringView Text;
        FColor Color = FColor(255, 255, 255, 255);
        uint8 Size = 20;
    };
}
