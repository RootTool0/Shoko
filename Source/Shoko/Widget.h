#pragma once

#include "Core/Aliases.h"
#include "Core/Macros.h"

struct SDL_Renderer;

namespace Shoko
{
    class FWidgetBase
    {
    public:
        GUTID_t LocalGUTID = 0;

        constexpr FWidgetBase(GUTID_t InGUTID) : LocalGUTID(InGUTID) {}
    };
    
    template<typename TDerivedWidget>
    class SWidget : public FWidgetBase
    {
        SHOKO_GENERATED_BODY()
        
    public:
        constexpr SWidget() : FWidgetBase(TDerivedWidget::GUTID) {}
        
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
        constexpr const FWidgetBase* GetWidgetAt(int16 InMouseX, int16 InMouseY) const
        {
            return HitTest(InMouseX, InMouseY) ? static_cast<const FWidgetBase*>(this) : nullptr;
        }
        
    protected:
        int16 X = 0;
        int16 Y = 0;
        int16 Width = 100;
        int16 Height = 50;
    };
}
