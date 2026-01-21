#pragma once

#include "Renderer.h"
#include "Styles.h"
#include "Widget.h"

namespace Shoko
{
    using CheckBoxHandler = void(*)(bool bValue);
    
    class SCheckBox : public SWidget<SCheckBox>
    {
        SHOKO_GENERATED_BODY(SCheckBox)
        
    public:
        constexpr SCheckBox() { Geometry.Size = FSize(24, 24); }
        
        constexpr SCheckBox& OnValueChanged(CheckBoxHandler InValueChangedHandler)
        {
            OnValueChangedHandler = InValueChangedHandler;
            return *this;
        }
        
        constexpr void CallOnMouseUp() const { bValue = !bValue; if(OnValueChangedHandler) OnValueChangedHandler(bValue); }
        
        void Render() const
        {
            if(bValue)
                FShokoRenderer::DrawRect(Geometry.Location, Geometry.Size, FShokoStyle::Action);
            else
            {
                FShokoRenderer::DrawRect(Geometry.Location, Geometry.Size, FShokoStyle::BackgroundPanelDark);
                FShokoRenderer::DrawRectBorder(Geometry.Location, Geometry.Size, FShokoStyle::ActionDisabled, 2, EShokoRendererBorderType::Inside);
            }
        }
        
    private:
        mutable bool bValue = false;
        CheckBoxHandler OnValueChangedHandler = nullptr;
    };
}

