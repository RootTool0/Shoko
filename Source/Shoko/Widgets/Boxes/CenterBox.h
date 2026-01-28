#pragma once

#include "Widgets/Base/WidgetWrapper.h"
#include "Core/Macros.h"
#include "Core/Meta.h"
#include "Types/Vector2D.h"

namespace Shoko
{
    template<typename TChildWidget>
    class SCenterBox : public SWidgetWrapper<SCenterBox<TChildWidget>, TChildWidget>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        using Super = SWidgetWrapper<SCenterBox<TChildWidget>, TChildWidget>;
        
    public:
        explicit constexpr SCenterBox(TChildWidget InChildWidget) : Super(Meta::Move(InChildWidget)) { CalculateLayout(); }
        
        constexpr SCenterBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }
        
        constexpr SCenterBox& SetLocation(FLocation InLocation)
        {
            Super::SetLocation(InLocation);
            CalculateLayout();
            return *this;
        }

    private:
        constexpr void CalculateLayout()
        {
            Super::ChildWidget.SetLocation(FGeometry::GetCenterLocation(Super::GetGeometry(), Super::ChildWidget.GetGeometry()));
        }
    };
}
