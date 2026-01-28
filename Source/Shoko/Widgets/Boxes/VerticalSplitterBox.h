#pragma once

#include "Widgets/Base/WidgetContainer.h"
#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename TChildWidgetUp, typename TChildWidgetDown>
    class SVerticalSplitterBox : public SWidgetContainer<TChildWidgetUp, TChildWidgetDown>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TChildWidgetUp> && Meta::IsWidget<TChildWidgetDown>,
            "Похоже, что не все дети в контейнере (SHorizontalBox) являются виджетами (SWidget)\n"
            "Простите, но думаю вы случайно добавили что-то неподходящее..\n"
            "Проверьте - все-ли элементы унаследованы от SWidget?..");
        
        using Super = SWidgetContainer<TChildWidgetUp, TChildWidgetDown>;
        
    public:
        explicit constexpr SVerticalSplitterBox(TChildWidgetUp&& InChildWidgetUp, TChildWidgetDown&& InChildWidgetDown) : Super(Meta::Move(InChildWidgetUp), Meta::Move(InChildWidgetDown)) { CalculateLayout(); }
        
        constexpr SVerticalSplitterBox& SetLocation(FLocation InLocation)
        {
            Super::SetLocation(InLocation);
            CalculateLayout();
            return *this;
        }
        
        constexpr SVerticalSplitterBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }
        
        constexpr SVerticalSplitterBox& SetAlpha(uint8 InAlpha)
        {
            Alpha = InAlpha;
            CalculateLayout();
            return *this;
        }
        
    private:
        uint8 Alpha = 127;
        
        constexpr void CalculateLayout()
        {
            const FGeometry& TotalGeo = Super::GetGeometry();
            
            const int16 UpHeight = static_cast<int16>((static_cast<uint32>(TotalGeo.Height()) * Alpha) / 255);
            const int16 DownHeight = TotalGeo.Height() - UpHeight;
            
            auto& UpWidget   = Super::template GetChild<0>();
            auto& DownWidget = Super::template GetChild<1>();
            
            UpWidget  .SetLocation(TotalGeo.Location);
            DownWidget.SetLocation(TotalGeo.Location + FLocation(0, UpHeight));
            
            UpWidget  .SetSize(FSize(TotalGeo.Width(), UpHeight));
            DownWidget.SetSize(FSize(TotalGeo.Width(), DownHeight));
        }
    };
}
