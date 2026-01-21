#pragma once

#include "Renderer.h"
#include "Styles.h"
#include "Widget.h"

namespace Shoko
{
    using ToggleHandler = void(*)(bool bState);
    
    class SToggle : public SWidget<SToggle>
    {
        SHOKO_GENERATED_BODY(SToggle)
        
    public:
        constexpr SToggle() { Geometry.Size = FSize(60, 28); }
        
        constexpr SToggle& OnStateChanged(ToggleHandler InStateChangedHandler)
        {
            OnStateChangedHandler = InStateChangedHandler;
            return *this;
        }
        
        constexpr void CallOnMouseUp() const { bState = !bState; if(OnStateChangedHandler) OnStateChangedHandler(bState); }
        
        void Render() const
        {
            const uint8 Radius = Geometry.Size.GetMin() / 2;
            static constexpr uint8 Offset = 4;
            
            if(bState)
            {
                FShokoRenderer::DrawRoundedRect(Geometry.Location, Geometry.Size, Radius, FShokoStyle::Action);
                FShokoRenderer::DrawCircle(Geometry.Location + FLocation(Geometry.Size.X - Radius, Radius), Radius - Offset, FShokoStyle::BackgroundPanelDark);
            }
            else
            {
                FShokoRenderer::DrawRoundedRect(Geometry.Location, Geometry.Size, Radius, FShokoStyle::BackgroundPanelDark);
                FShokoRenderer::DrawCircle(Geometry.Location + FLocation(Radius), Radius - Offset, FShokoStyle::ActionDisabled);
            }
        }
        
    private:
        mutable bool bState = false;
        ToggleHandler OnStateChangedHandler = nullptr;
    };
}
