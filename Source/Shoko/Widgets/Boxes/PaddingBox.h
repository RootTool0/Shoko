#pragma once

#include "Core/Meta.h"
#include "Types/Vector2D.h"
#include "Types/Geometry.h"

namespace Shoko
{
    template<typename TChildWidget>
    class SPaddingBox : public SWidgetWrapper<SPaddingBox<TChildWidget>, TChildWidget>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        using Super = SWidgetWrapper<SPaddingBox<TChildWidget>, TChildWidget>;
        
    public:
        FPadding Padding;

        explicit constexpr SPaddingBox(TChildWidget InChildWidget) : Super(Meta::Move(InChildWidget)) { CalculateLayout(); }
        
        constexpr SPaddingBox& SetPadding(FPadding InPadding)
        {
            Padding = InPadding;
            CalculateLayout();
            return *this;
        }
        
        constexpr SPaddingBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }
        
        constexpr SPaddingBox& SetLocation(FLocation InLocation)
        {
            Super::SetLocation(InLocation);
            CalculateLayout();
            return *this;
        }

    private:
        constexpr void CalculateLayout()
        {
            FGeometry Geometry = FGeometry::GetGeometryPaddingByParent(Super::GetGeometry(), Padding);
            Super::ChildWidget.SetLocation(Geometry.Location);
            Super::ChildWidget.SetSize(Geometry.Size);
        }
    };
}
