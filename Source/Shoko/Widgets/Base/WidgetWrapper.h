#pragma once

#include "Core/Meta.h"
#include "Widget.h"

namespace Shoko
{
    template<typename TDerivedWidget, typename TChildWidget>
    class SWidgetWrapper : public SWidget<TDerivedWidget>
    {
        static_assert(Meta::IsWidget<TChildWidget>, "SWidgetWrapper child must be SWidget");

        using Super = SWidget<TDerivedWidget>;
        
    public:
        TChildWidget ChildWidget;
        
        explicit constexpr SWidgetWrapper(TChildWidget&& InChildWidget) : ChildWidget(Meta::Move(InChildWidget)) {}
        
        constexpr void Render() const { ChildWidget.Render(); }
        
        constexpr const FWidgetBase* HitTest(FLocation InMouseLocation) const { return ChildWidget.HitTest(InMouseLocation); }
    };
}
