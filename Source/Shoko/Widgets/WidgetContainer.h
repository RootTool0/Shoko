#pragma once

#include "Widget.h"
#include "Core/Meta.h"
#include "Core/Macros.h"
#include "Types/Tuple.h"

namespace Shoko
{
    template<typename... TChildWidgets>
    class SWidgetContainer : public SWidget<SWidgetContainer<TChildWidgets...>>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        SHOKO_STATIC_ASSERT((Meta::IsWidget<TChildWidgets> && ...),
            "Похоже, что не все дети в контейнере (SWidgetContainer) являются виджетами (SWidget)\n"
            "Простите, но думаю вы случайно добавили что-то неподходящее..\n"
            "Проверьте - все-ли элементы унаследованы от SWidget?..");
        
        using Super = SWidget<SWidgetContainer<TChildWidgets...>>;
        
    public:
        uint8 ChildWidgetsCount;
        TTuple<TChildWidgets...> ChildWidgets;
        
        explicit constexpr SWidgetContainer(TChildWidgets&&... InChildWidgets) : ChildWidgetsCount(static_cast<uint8>(sizeof...(TChildWidgets))), ChildWidgets(Meta::Move(InChildWidgets)...) {}

        template <size_t Index>
        constexpr auto& Get() &
        {
            SHOKO_STATIC_ASSERT(Index < sizeof...(TChildWidgets),
                "Индекс вышел за пределы размера контейнера (SWidgetContainer)\n"
                "Я думаю вы пытаетесь получить больше, чем то, что у меня есть..\n"
                "Может в следующий раз стоит быть осторожнее и выбирать индексы поменьше?..");
            
            return ChildWidgets.template Get<Index>();
        }
        
        template <size_t Index>
        constexpr const auto& Get() const &
        {
            SHOKO_STATIC_ASSERT(Index < sizeof...(TChildWidgets),
                "Индекс вышел за пределы размера контейнера (SWidgetContainer)\n"
                "Я думаю вы пытаетесь получить больше, чем то, что у меня есть..\n"
                "Может в следующий раз стоит быть осторожнее и выбирать индексы поменьше?..");
            
            return ChildWidgets.template Get<Index>();
        }
        
        constexpr const FWidgetBase* HitTest(FIntVector2D InMouseLocation) const
        {
            if(!Super::HitTest(InMouseLocation)) return nullptr;
            
            const FWidgetBase* FoundWidget = nullptr;
            Meta::Apply([&](const auto&... Child) { ((FoundWidget = Child.HitTest(InMouseLocation), FoundWidget != nullptr) || ...); }, ChildWidgets);
            return FoundWidget ? FoundWidget : static_cast<const FWidgetBase*>(this);
        }
        
        constexpr void Render() const { Meta::Apply([&](const auto&... Child) { (Child.Render(), ...); }, ChildWidgets); }
    };
}
