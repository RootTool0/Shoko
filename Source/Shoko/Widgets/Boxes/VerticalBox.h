#pragma once

#include "Widgets/Base/WidgetContainer.h"
#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename... TChildWidgets>
    class SVerticalBox : public SWidgetContainer<TChildWidgets...>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        SHOKO_STATIC_ASSERT((Meta::IsWidget<TChildWidgets> && ...),
            "Похоже, что не все дети в контейнере (SVerticalBox) являются виджетами (SWidget)\n"
            "Простите, но думаю вы случайно добавили что-то неподходящее..\n"
            "Проверьте - все-ли элементы унаследованы от SWidget?..");
        
        using Super = SWidgetContainer<TChildWidgets...>;
        
    public:
        explicit constexpr SVerticalBox(TChildWidgets&&... InChildren) : Super(Meta::Move(InChildren)...) { CalculateLayout(); }
        
        constexpr SVerticalBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }

        constexpr SVerticalBox& SetLocation(FLocation InLocation)
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
            
            const uint16 Width =  Super::GetGeometry().Width();
            const uint16 Height = Super::GetGeometry().Height();
            
            const int16 ChildHeight = Height / Count;
            int16 CursorY = Super::GetGeometry().Y();

            Meta::Apply(
                [&](auto&... Child)
                {
                    ((
                        Child.SetLocation(FLocation(Super::GetGeometry().X(), CursorY)),
                        Child.SetSize(FSize(Width, ChildHeight)),
                        CursorY += ChildHeight
                    ), ...);
                },
                this->ChildWidgets
            );
        }
    };
}
