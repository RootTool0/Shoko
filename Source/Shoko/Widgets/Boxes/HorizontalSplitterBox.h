#pragma once

#include "Widgets/Base/WidgetContainer.h"
#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename TChildWidgetLeft, typename TChildWidgetRight>
    class SHorizontalSplitterBox : public SWidgetContainer<TChildWidgetLeft, TChildWidgetRight>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TChildWidgetLeft> && Meta::IsWidget<TChildWidgetRight>,
            "Похоже, что не все дети в контейнере (SHorizontalBox) являются виджетами (SWidget)\n"
            "Простите, но думаю вы случайно добавили что-то неподходящее..\n"
            "Проверьте - все-ли элементы унаследованы от SWidget?..");
        
        using Super = SWidgetContainer<TChildWidgetLeft, TChildWidgetRight>;
        
    public:
        explicit constexpr SHorizontalSplitterBox(TChildWidgetLeft&& InChildWidgetLeft, TChildWidgetRight&& InChildWidgetRight) : Super(Meta::Move(InChildWidgetLeft), Meta::Move(InChildWidgetRight)) { CalculateLayout(); }
        
        constexpr SHorizontalSplitterBox& SetLocation(FLocation InLocation)
        {
            Super::SetLocation(InLocation);
            CalculateLayout();
            return *this;
        }
        
        constexpr SHorizontalSplitterBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }
        
        constexpr SHorizontalSplitterBox& SetAlpha(uint8 InAlpha)
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
            
            const int16 LeftWidth = static_cast<int16>((static_cast<uint32>(TotalGeo.Width()) * Alpha) / 255);
            const int16 RightWidth = TotalGeo.Width() - LeftWidth;
            
            auto& LeftWidget  = Super::template GetChild<0>();
            auto& RightWidget = Super::template GetChild<1>();
            
            LeftWidget .SetLocation(TotalGeo.Location);
            RightWidget.SetLocation(TotalGeo.Location + FLocation(LeftWidth, 0));
            
            LeftWidget .SetSize(FSize(LeftWidth , TotalGeo.Height()));
            RightWidget.SetSize(FSize(RightWidth, TotalGeo.Height()));
        }
    };
}
