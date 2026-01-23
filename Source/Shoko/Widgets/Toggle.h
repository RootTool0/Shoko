#pragma once

#include "Renderer.h"
#include "Style.h"
#include "Widget.h"

namespace Shoko
{
    using ToggleHandler = void(*)(bool bValue);
    
    class SToggle : public SWidget<SToggle>
    {
        SHOKO_GENERATED_BODY(SToggle)
        
    public:
        constexpr SToggle() { Geometry.Size = FSize(60, 28); }
        
        constexpr SToggle& OnValueChanged(ToggleHandler InValueChangedHandler)
        {
            OnValueChangedHandler = InValueChangedHandler;
            return *this;
        }
        
        constexpr void CallOnMouseUp() const { bValue = !bValue; if(OnValueChangedHandler) OnValueChangedHandler(bValue); }
        
        void Render() const
        {
            const uint8 Radius = Geometry.Size.GetMin() / 2;
            static constexpr uint8 Offset = 4;
            
            if(bValue)
            {
                FShokoRenderer::DrawRoundedRect(Geometry.Location, Geometry.Size, Radius, FStyle::Action);
                FShokoRenderer::DrawCircle(Geometry.Location + FLocation(Geometry.Size.X - Radius, Radius), Radius - Offset, FStyle::BackgroundPanelDark);
            }
            else
            {
                FShokoRenderer::DrawRoundedRect(Geometry.Location, Geometry.Size, Radius, FStyle::BackgroundPanelDark);
                FShokoRenderer::DrawCircle(Geometry.Location + FLocation(Radius), Radius - Offset, FStyle::ActionDisabled);
            }
        }
        
    private:
        mutable bool bValue = false;
        ToggleHandler OnValueChangedHandler = nullptr;
    };
}
