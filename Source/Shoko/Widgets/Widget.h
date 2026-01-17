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
        SHOKO_GENERATED_BODY_TEMPLATE(1)
        
    public:
        constexpr SWidget() : FWidgetBase(TDerivedWidget::GUTID) {}
        
        constexpr TDerivedWidget& SetSize(const int16 InWidth, const int16 InHeight)
        {
            Geometry.Size.X = InWidth; 
            Geometry.Size.Y = InHeight;
            return static_cast<TDerivedWidget&>(*this);
        }
    
        constexpr TDerivedWidget& SetPosition(const int16 InX, const int16 InY)
        {
            Geometry.Location.X = InX;
            Geometry.Location.Y = InY;
            return static_cast<TDerivedWidget&>(*this);
        }
    
        constexpr int16 GetX() const      { return Geometry.Location.X; }
        constexpr int16 GetY() const      { return Geometry.Location.Y; }
        constexpr int16 GetWidth() const  { return Geometry.Size.X; }
        constexpr int16 GetHeight() const { return Geometry.Size.Y; }
    
        // constexpr void Render() const { static_cast<const TDerivedWidget*>(this)->Render(); }
        constexpr void Render() const { TDerivedWidget::Render(); }
        constexpr const FWidgetBase* HitTest(FIntVector2D InMouseLocation) const { return Geometry.Contains(InMouseLocation) ? static_cast<const FWidgetBase*>(this) : nullptr; }
        
    protected:
        FGeometry Geometry;
    };
}
