#pragma once

#include <SDL_render.h>

#include "Widget.h"
#include "Types/Color.h"

namespace Shoko
{
    class SBoxWidget : public SWidget<SBoxWidget>
    {
        
    public:
        constexpr SBoxWidget& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        void Render(SDL_Renderer* InRenderer) const
        {
            SDL_SetRenderDrawColor(InRenderer, Color.R, Color.G, Color.B, Color.A);
            SDL_Rect Rect = {X, Y, Width, Height};
            SDL_RenderFillRect(InRenderer, &Rect);
        }
        
    protected:
        FColor Color = FColor(0, 0, 0, 0);
        
    };
}
