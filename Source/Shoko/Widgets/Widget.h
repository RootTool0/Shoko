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
        
        constexpr int16 GetX() const      { return Geometry.Location.X; }
        constexpr int16 GetY() const      { return Geometry.Location.Y; }
        constexpr int16 GetWidth() const  { return Geometry.Size.X; }
        constexpr int16 GetHeight() const { return Geometry.Size.Y; }
        
        constexpr void Render() const { static_cast<const TDerivedWidget*>(this)->Render(); }
        // constexpr void Render() const { TDerivedWidget::Render(); }
        constexpr const FWidgetBase* HitTest(FLocation InMouseLocation) const { return Geometry.Contains(InMouseLocation) ? static_cast<const FWidgetBase*>(this) : nullptr; }
        
    // protected:
        FGeometry Geometry;
    };
}
