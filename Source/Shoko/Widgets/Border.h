#pragma once

#include "WidgetWrapper.h"
#include "Types/Color.h"

namespace Shoko
{
    enum class EBorderType : uint8 { Inside, Outside, Both };
    
    template<typename TChildWidget>
    class SBorder : public SWidgetWrapper<SBorder<TChildWidget>, TChildWidget>
    {
        uint8 Thickness = 1;
        EBorderType Type = EBorderType::Inside;
        FColor Color = FColor(255, 0, 0);
        
        using Base = SWidgetWrapper<SBorder<TChildWidget>, TChildWidget>;
        using Base::ChildWidget;
        
    public:
        template<typename T>
        explicit constexpr SBorder(T&& InChildWidget) : Base(Meta::Forward<T>(InChildWidget))
        {
            this->X = ChildWidget.GetX();
            this->Y = ChildWidget.GetY();
            this->Width = ChildWidget.GetWidth();
            this->Height = ChildWidget.GetHeight();
        }
        
        constexpr SBorder& SetType(EBorderType InType)
        {
            Type = InType;
            return *this;
        }
        
        constexpr SBorder& SetThickness(uint8 InThickness)
        {
            Thickness = InThickness;
            return *this;
        }
        
        constexpr SBorder& SetColor(FColor InColor)
        {
            Color = InColor;
            return *this;
        }
        
        constexpr void Render() const
        {
            /*ChildWidget.Render(InRenderer);

            SDL_SetRenderDrawColor(InRenderer, Color.R, Color.G, Color.B, Color.A);
            auto Draw = [&](const SDL_Rect& R)
            {
                SDL_RenderFillRect(InRenderer, &R);
            };
            
            switch (Type)
            {
            case EBorderType::Inside:
                Draw({ ChildWidget.GetX()                           , ChildWidget.GetY(), ChildWidget.GetWidth(), Thickness });
                Draw({ ChildWidget.GetX()                           , ChildWidget.GetY() + ChildWidget.GetHeight() - Thickness, ChildWidget.GetWidth(), Thickness });
                Draw({ ChildWidget.GetX()                           , ChildWidget.GetY() + Thickness, Thickness, ChildWidget.GetHeight() - 2 * Thickness });
                Draw({ ChildWidget.GetX() + ChildWidget.GetWidth() - Thickness, ChildWidget.GetY() + Thickness, Thickness, ChildWidget.GetHeight() - 2 * Thickness });
                break;
            
            case EBorderType::Outside:
                Draw({ ChildWidget.GetX() - Thickness, ChildWidget.GetY() - Thickness, ChildWidget.GetWidth() + 2 * Thickness, Thickness });
                Draw({ ChildWidget.GetX() - Thickness, ChildWidget.GetY() + ChildWidget.GetHeight(), ChildWidget.GetWidth() + 2 * Thickness, Thickness });
                Draw({ ChildWidget.GetX() - Thickness, ChildWidget.GetY(), Thickness, ChildWidget.GetHeight() });
                Draw({ ChildWidget.GetX() + ChildWidget.GetWidth(), ChildWidget.GetY(), Thickness, ChildWidget.GetHeight() });
                break;
            
            case EBorderType::Both:
                {
                    const uint8 HalfThickness = Thickness / 2;
                    
                    Draw({ ChildWidget.GetX() - HalfThickness, ChildWidget.GetY() - HalfThickness, ChildWidget.GetWidth() + Thickness, Thickness });
                    Draw({ ChildWidget.GetX() - HalfThickness, ChildWidget.GetY() + ChildWidget.GetHeight() - HalfThickness, ChildWidget.GetWidth() + Thickness, Thickness });
                    Draw({ ChildWidget.GetX() - HalfThickness, ChildWidget.GetY() + HalfThickness, Thickness, ChildWidget.GetHeight() - Thickness });
                    Draw({ ChildWidget.GetX() + ChildWidget.GetWidth() - HalfThickness, ChildWidget.GetY() + HalfThickness, Thickness, ChildWidget.GetHeight() - Thickness });
                    break;
                }
            }*/
        }
    };
}
