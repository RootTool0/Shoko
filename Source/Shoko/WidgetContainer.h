#pragma once

#include <tuple>

#include "Widget.h"
#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename... TChildWidgets>
    class SWidgetContainer : public SWidget<SWidgetContainer<TChildWidgets...>>
    {
        SHOKO_STATIC_ASSERT((Meta::IsWidget<TChildWidgets> && ...),
            "Похоже, что не все дети в контейнере (SWidgetContainer) являются виджетами (SWidget)\n"
            "Простите, но думаю вы случайно добавили что-то неподходящее..\n"
            "Проверьте - все-ли элементы унаследованы от SWidget?..");
    
    public:
        std::tuple<TChildWidgets...> ChildWidgets;
        
        explicit constexpr SWidgetContainer(TChildWidgets&&... InChildWidgets) : ChildWidgets(Meta::Move(InChildWidgets)...)
        {
            SWidget<SWidgetContainer<TChildWidgets...>>::X = 0;
            SWidget<SWidgetContainer<TChildWidgets...>>::Y = 0;
            SWidget<SWidgetContainer<TChildWidgets...>>::Width = 800;
            SWidget<SWidgetContainer<TChildWidgets...>>::Height = 600;
        }

        /*
        template <size_t Index>
        constexpr auto& GetChildByIndex() { return std::get<Index>(ChildWidgets); }
        */

        template <size_t Index>
        constexpr auto& GetChildByIndex() &
        {
            SHOKO_STATIC_ASSERT(Index < sizeof...(TChildWidgets),
                "Индекс вышел за пределы размера контейнера (SWidgetContainer)\n"
                "Я думаю вы пытаетесь получить больше, чем то, что у меня есть..\n"
                "Может в следующий раз стоит быть осторожнее и выбирать индексы поменьше?..");
            
            return std::get<Index>(ChildWidgets);
        }
        
        template <size_t Index>
        constexpr const auto& GetChildByIndex() const &
        {
            SHOKO_STATIC_ASSERT(Index < sizeof...(TChildWidgets),
                "Индекс вышел за пределы размера контейнера (SWidgetContainer)\n"
                "Я думаю вы пытаетесь получить больше, чем то, что у меня есть..\n"
                "Может в следующий раз стоит быть осторожнее и выбирать индексы поменьше?..");
            
            return std::get<Index>(ChildWidgets);
        }
        
        constexpr const void* GetWidgetAt(int16 InMouseX, int16 InMouseY) const
        {
            if (!this->HitTest(InMouseX, InMouseY))
                return nullptr;

            const void* found = nullptr;

            // РџСЂРѕРІРµСЂСЏРµРј РІСЃРµС… РґРµС‚РµР№
            std::apply([&](const auto&... child){
                // РџСЂРѕРІРµСЂСЏРµРј РґРµС‚РµР№ РІ РѕР±СЂР°С‚РЅРѕРј РїРѕСЂСЏРґРєРµ (РїРѕСЃР»РµРґРЅРёР№ РґРѕР±Р°РІР»РµРЅРЅС‹Р№ - СЃРІРµСЂС…Сѓ)
                auto checkChild = [&](const auto& widget) {
                    if (auto* result = widget.GetWidgetAt(InMouseX, InMouseY)) {
                        found = result;
                        return true; // РќР°С€Р»Рё
                    }
                    return false;
                };
        
                // РџСЂРѕРІРµСЂСЏРµРј РґРѕ РїРµСЂРІРѕРіРѕ РЅР°Р№РґРµРЅРЅРѕРіРѕ
                (checkChild(child) || ...);
            }, ChildWidgets);

            // Р’РђР–РќРћ: РљРѕРЅС‚РµР№РЅРµСЂ РќРРљРћР“Р”Рђ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ СЃРµР±СЏ!
            // РўРѕР»СЊРєРѕ РґРѕС‡РµСЂРЅРёРµ РІРёРґР¶РµС‚С‹ РёР»Рё nullptr
            return found;
        }
        void Render(SDL_Renderer* InRenderer) const
        {
            std::apply([&](const auto&... child) {
                (child.Render(InRenderer), ...);  // Fold expression!
            }, ChildWidgets);
        }
        
        /*
        constexpr const TDerivedWidget* GetWidgetAt(int16 InMouseX, int16 InMouseY) const
        {
            if(!this->HitTest(InMouseX, InMouseY)) return nullptr;
            
            const TDerivedWidget* FoundWidget = nullptr;
            std::apply([&](auto&... ChildWidget){ ((FoundWidget = ChildWidget.GetWidgetAt(InMouseX, InMouseY)) || ...); }, ChildWidgets);
            return FoundWidget ? FoundWidget : static_cast<const TDerivedWidget*>(this);
        }*/
    };
}
