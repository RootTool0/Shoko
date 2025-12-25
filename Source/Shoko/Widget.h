#pragma once

#include "Core/Aliases.h"

struct SDL_Renderer;

namespace Shoko
{
    template<typename TDerivedWidget>
    class SWidget
    {
        
    public:
        constexpr SWidget() = default;
    
        constexpr TDerivedWidget& SetSize(const int16 InWidth, const int16 InHeight)
        {
            Width = InWidth; 
            Height = InHeight;
            return static_cast<TDerivedWidget&>(*this);
        }
    
        constexpr TDerivedWidget& SetPosition(const int16 InX, const int16 InY)
        {
            X = InX;
            Y = InY;
            return static_cast<TDerivedWidget&>(*this);
        }
    
        constexpr int16 GetX() const { return X; }
        constexpr int16 GetY() const { return Y; }
        constexpr int16 GetWidth() const { return Width; }
        constexpr int16 GetHeight() const { return Height; }
    
        void Render(SDL_Renderer* InRenderer) const { static_cast<const TDerivedWidget*>(this)->Render(InRenderer); }

        constexpr bool HitTest(int16 InX, int16 InY) const { return InX >= X && InX <= X + Width && InY >= Y && InY <= Y + Height; }
        constexpr const void* GetWidgetAt(int16 InMouseX, int16 InMouseY) const
        {
            return HitTest(InMouseX, InMouseY) ? static_cast<const void*>(this) : nullptr;
        }
        
    protected:
        int16 X = 0;
        int16 Y = 0;
        int16 Width = 100;
        int16 Height = 50;
    };
}
