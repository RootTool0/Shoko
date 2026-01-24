#pragma once

#include "WidgetContainer.h"
#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename... TChildWidgets>
    class SHorizontalBox : public SWidgetContainer<TChildWidgets...>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        SHOKO_STATIC_ASSERT((Meta::IsWidget<TChildWidgets> && ...),
            "Похоже, что не все дети в контейнере (SHorizontalBox) являются виджетами (SWidget)\n"
            "Простите, но думаю вы случайно добавили что-то неподходящее..\n"
            "Проверьте - все-ли элементы унаследованы от SWidget?..");
        
        using Super = SWidgetContainer<TChildWidgets...>;
        
    public:
        explicit constexpr SHorizontalBox(TChildWidgets&&... InChildren) : Super(Meta::Move(InChildren)...) { CalculateLayout(); }
        
        constexpr SHorizontalBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }

        constexpr SHorizontalBox& SetLocation(FLocation InLocation)
        {
            Super::SetLocation(InLocation);
            CalculateLayout();
            return *this;
        }
        
    private:
        constexpr void CalculateLayout()
        {
            const uint8 Count = this->ChildWidgetsCount;
            if(Count == 0) return;
            
            const int16 Width = Super::Geometry.Width() / Count;
            int16 CursorX = Super::Geometry.X();

            Meta::Apply(
                [&](auto&... Child)
                {
                    ((
                        Child.SetLocation(FLocation(CursorX, Super::Geometry.Y())),
                        Child.SetSize(FSize(Width, Super::Geometry.Height())),
                        CursorX += Width
                    ), ...);
                },
                this->ChildWidgets
            );
        }
    };
}
