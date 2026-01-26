#pragma once

#include "Input.h"
#include "Renderer.h"
#include "Style.h"
#include "Widget.h"

namespace Shoko
{
    using SliderHandler = void(*)(float Alpha);
    
    SHOKO_CLASS(SSlider)
    class SSlider : public SWidget<SSlider>
    {
        SHOKO_GENERATED_BODY(SSlider)
        
    public:
        constexpr SSlider() { SetSize(FSize(300, 14)); }
        
        constexpr SSlider& OnValueChanged(SliderHandler InValueChangedHandler)
        {
            OnValueChangedHandler = InValueChangedHandler;
            return *this;
        }
        
        constexpr SSlider& OnValueChangeFinished(SliderHandler InValueChangeFinishedHandler)
        {
            OnValueChangeFinishedHandler = InValueChangeFinishedHandler;
            return *this;
        }
        
        void CallOnMouseMove() const
        {
            const float AlphaNormalized = FMath::Clamp((static_cast<float>(FShokoInput::GetMousePosition().X) - static_cast<float>(GetGeometry().Left())) / static_cast<float>(GetGeometry().Width()), 0.f, 1.f);
            Alpha = static_cast<uint8>(AlphaNormalized * 255.0f);
            
            if(OnValueChangedHandler) OnValueChangedHandler(AlphaNormalized);
        }
        
        void CallOnMouseUp() const
        {
            const float AlphaNormalized = FMath::Clamp((static_cast<float>(FShokoInput::GetMousePosition().X) - static_cast<float>(GetGeometry().Left())) / static_cast<float>(GetGeometry().Width()), 0.f, 1.f);            
            if(OnValueChangeFinishedHandler) OnValueChangeFinishedHandler(static_cast<float>(Alpha) / 255.f);
        }
        
        void Render() const
        {
            const uint8 Radius = GetGeometry().Size.GetMin() / 2;
            const uint16 Width = GetGeometry().Size.X * Alpha / 255;

            FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, FStyle::BackgroundPanelDark);
            FShokoRenderer::DrawRoundedRect(GetGeometry().Location, FSize(Width, GetGeometry().Size.Y), Radius, FStyle::Action);
        }
        
    private:
        mutable uint8 Alpha = 0;
        SliderHandler OnValueChangedHandler = nullptr;
        SliderHandler OnValueChangeFinishedHandler = nullptr;
    };
}
