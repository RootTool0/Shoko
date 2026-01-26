#pragma once

#include "Renderer.h"
#include "Style.h"
#include "Widget.h"

namespace Shoko
{
    using ToggleHandler = void(*)(bool bValue);
    
    SHOKO_CLASS(SToggle)
    class SToggle : public SWidget<SToggle>
    {
        SHOKO_GENERATED_BODY(SToggle)
        
    public:
        constexpr SToggle() { SetSize(FSize(60, 28)); }
        
        constexpr SToggle& OnValueChanged(ToggleHandler InValueChangedHandler)
        {
            OnValueChangedHandler = InValueChangedHandler;
            return *this;
        }
        
        constexpr void CallOnMouseUp() const { bValue = !bValue; if(OnValueChangedHandler) OnValueChangedHandler(bValue); }
        
        void Render() const
        {
            const uint8 Radius = GetGeometry().Size.GetMin() / 2;
            static constexpr uint8 Offset = 4;
            
            if(bValue)
            {
                FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, FStyle::Action);
                FShokoRenderer::DrawCircle(GetGeometry().Location + FLocation(static_cast<int16>(GetGeometry().Size.X - Radius), Radius), Radius - Offset, FStyle::BackgroundPanelDark);
            }
            else
            {
                FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, FStyle::BackgroundPanelDark);
                FShokoRenderer::DrawCircle(GetGeometry().Location + FLocation(Radius), Radius - Offset, FStyle::ActionDisabled);
            }
        }
        
    private:
        mutable bool bValue = false;
        ToggleHandler OnValueChangedHandler = nullptr;
    };
}
