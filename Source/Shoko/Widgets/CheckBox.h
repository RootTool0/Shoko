#pragma once

#include "Base/Widget.h"
#include "Renderer.h"
#include "Style.h"

namespace Shoko
{
    using CheckBoxHandler = void(*)(bool bValue);
    
    SHOKO_CLASS(SCheckBox)
    class SCheckBox : public SWidget<SCheckBox>
    {
        SHOKO_GENERATED_BODY(SCheckBox)
        
    public:
        constexpr SCheckBox() { SetSize(FSize(24, 24)); }
        
        constexpr SCheckBox& OnValueChanged(CheckBoxHandler InValueChangedHandler)
        {
            OnValueChangedHandler = InValueChangedHandler;
            return *this;
        }
        
        constexpr void CallOnMouseUp() const { bValue = !bValue; if(OnValueChangedHandler) OnValueChangedHandler(bValue); }
        
        void Render() const
        {
            if(bValue)
                FShokoRenderer::DrawRect(GetGeometry().Location, GetGeometry().Size, FStyle::Action);
            else
            {
                FShokoRenderer::DrawRect(GetGeometry().Location, GetGeometry().Size, FStyle::BackgroundPanelDark);
                FShokoRenderer::DrawRectBorder(GetGeometry().Location, GetGeometry().Size, FStyle::ActionDisabled, 2, EShokoRendererBorderType::Inside);
            }
        }
        
    private:
        mutable bool bValue = false;
        CheckBoxHandler OnValueChangedHandler = nullptr;
    };
}

