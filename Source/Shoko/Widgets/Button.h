#pragma once

#include "Style.h"
#include "Base/Widget.h"

namespace Shoko
{
    using HandlerPtr = void(*)();
    
    SHOKO_CLASS(SButton)
    class SButton : public SWidget<SButton>
    {
        SHOKO_GENERATED_BODY(SButton)
        
    public:
        constexpr SButton() = default;
        
        /*
        constexpr FColor GetColor() const { return Color; }
        constexpr SButton& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        */
        
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
        
        constexpr void CallOnMouseDown() const { ButtonState |=  static_cast<uint8>(EButtonState::MouseDown); if(OnMouseDownHandler) OnMouseDownHandler(); }
        constexpr void CallOnMouseUp()   const { ButtonState &= ~static_cast<uint8>(EButtonState::MouseDown); if(OnMouseUpHandler) OnMouseUpHandler(); }
        constexpr void CallOnHover()     const { ButtonState |=  static_cast<uint8>(EButtonState::Hover);     if(OnHoverHandler) OnHoverHandler(); }
        constexpr void CallOnUnhover()   const { ButtonState &= ~static_cast<uint8>(EButtonState::Hover);     if(OnUnhoverHandler) OnUnhoverHandler(); }
        
        void Render() const
        {
            static constexpr uint8 Radius = 8;
            
            if((ButtonState & static_cast<uint8>(EButtonState::MouseDown)) != 0)
            {
                FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, FStyle::Action);
                return;
            }
            
            FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, FStyle::BackgroundPanelDark);
            
            if((ButtonState & static_cast<uint8>(EButtonState::Hover)) != 0)
                FShokoRenderer::DrawRoundedRectBorder(GetGeometry().Location, GetGeometry().Size, Radius, FStyle::Border, 1, EShokoRendererBorderType::Inside);
            
            // FShokoRenderer::DrawRect(GetGeometry().Location, GetGeometry().Size, Color);
        }
        
    private:
        enum class EButtonState : uint8
        {
            Hover     = 1 << 1,
            MouseDown = 1 << 2,
            Disabled  = 1 << 3 
        };
        
        mutable uint8 ButtonState = 0;
        // FColor Color = FColor(255, 255, 255);
        
        HandlerPtr OnMouseDownHandler = nullptr;
        HandlerPtr OnMouseUpHandler = nullptr;
        HandlerPtr OnHoverHandler = nullptr;
        HandlerPtr OnUnhoverHandler = nullptr;
    };
}
