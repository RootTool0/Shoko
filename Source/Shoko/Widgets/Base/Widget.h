#pragma once

#include "Core/Aliases.h"
#include "Core/Macros.h"
#include "Types/Geometry.h"
#include "WidgetBase.h"

namespace Shoko
{
    template<typename TDerivedWidget>
    class SWidget : public FWidgetBase
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
    public:
        constexpr SWidget() : FWidgetBase(TDerivedWidget::StaticGUTID) {}
        
        constexpr TDerivedWidget& SetSize(FSize InSize)
        {
            Geometry.Size = InSize; 
            return static_cast<TDerivedWidget&>(*this);
        }
        
        constexpr TDerivedWidget& SetLocation(FLocation InLocation)
        {
            Geometry.Location = InLocation;
            return static_cast<TDerivedWidget&>(*this);
        }
        
        constexpr FGeometry GetGeometry() const { return Geometry; }
        
        constexpr void Render() const { static_cast<const TDerivedWidget*>(this)->Render(); }
        constexpr const FWidgetBase* HitTest(FLocation InMouseLocation) const { return Geometry.Contains(InMouseLocation) ? static_cast<const FWidgetBase*>(this) : nullptr; }
    
    private:
        FGeometry Geometry;
    };
}
