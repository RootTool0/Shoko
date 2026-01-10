#pragma once

#include "Widget.h"
#include "../Types/Color.h"

namespace Shoko
{
    using HandlerPtr = void(*)();
    
    class SButton : public SWidget<SButton>
    {
        SHOKO_GENERATED_BODY()
        
    public:
        constexpr SButton() = default;
        
        constexpr FColor GetColor() const { return Color; }
        constexpr SButton& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        constexpr SButton& OnMouseDown(HandlerPtr InMouseDownHandler)
        {
            OnMouseDownHandler = InMouseDownHandler;
            return *this;
        }
        
        constexpr SButton& OnMouseUp(HandlerPtr InMouseUpHandler)
        {
            OnMouseUpHandler = InMouseUpHandler;
            return *this;
        }
        
        constexpr SButton& OnHover(HandlerPtr InHoverHandler)
        {
            OnHoverHandler = InHoverHandler;
            return *this;
        }
        
        constexpr SButton& OnUnhover(HandlerPtr InUnhoverHandler)
        {
            OnUnhoverHandler = InUnhoverHandler;
            return *this;
        }
        
        
        constexpr void CallOnMouseDown() const
        {
            if(OnMouseDownHandler) OnMouseDownHandler();
        }
        
        constexpr void CallOnMouseUp() const
        {
            if(OnMouseUpHandler) OnMouseUpHandler();
        }
        
        constexpr void CallOnHover() const
        {
            if(OnHoverHandler) OnHoverHandler();
        }
        
        constexpr void CallOnUnhover() const
        {
            if(OnUnhoverHandler) OnUnhoverHandler();
        }
        
        void Render() const
        {
            FShokoRenderer::DrawRect(Geometry, Color);
        }
        
    private:
        enum class EButtonState : uint8
        {
            Normal,
            
            Hovered,
            MouseDown,
            Disabled
        };

        EButtonState ButtonState = EButtonState::Normal;
        FColor Color = FColor(255, 255, 255);
        
        HandlerPtr OnMouseDownHandler = nullptr;
        HandlerPtr OnMouseUpHandler = nullptr;
        HandlerPtr OnHoverHandler = nullptr;
        HandlerPtr OnUnhoverHandler = nullptr;
    };
}
