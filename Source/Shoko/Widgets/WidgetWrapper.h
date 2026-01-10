#pragma once

#include "Widget.h"
#include "../Core/Meta.h"

namespace Shoko
{
    template<typename TDerivedWidget, typename TChildWidget>
    class SWidgetWrapper : public SWidget<TDerivedWidget>
    {
        static_assert(Meta::IsWidget<TChildWidget>, "SWidgetWrapper child must be SWidget");

    public:
        TChildWidget ChildWidget;
        
        explicit constexpr SWidgetWrapper(TChildWidget&& InChildWidget) : ChildWidget(Meta::Move(InChildWidget)) {}
        
        constexpr const FWidgetBase* GetWidgetAt(int16 InMouseX, int16 InMouseY) const
        {
            if(!this->HitTest(InMouseX, InMouseY)) return nullptr;

            const FWidgetBase* FoundWidget = ChildWidget.GetWidgetAt(InMouseX, InMouseY);
            return FoundWidget ? FoundWidget : static_cast<const FWidgetBase*>(this);
        }
    };
}
