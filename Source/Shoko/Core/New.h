#pragma once

#include "Meta.h"
#include "Macros.h"

namespace Shoko
{
    template<typename TWidget>
    constexpr auto SNew()
    {        
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        SHOKO_STATIC_ASSERT(Meta::HasGUTID<TWidget>,
            "Кажется Вы забыли макрос SHOKO_GENERATED_BODY() внутри класса виджета.\n"
            "Стесняюсь рассказывать Вам всю магию этого макроса, задуманным моим создателем...\n"
            "Просто добавьте макрос SHOKO_GENERATED_BODY() в свой виджет и продолжим!");
        
        return TWidget();
    }
    
    template<typename TWidget, typename... TArgs>
    constexpr auto SNew(TArgs&&... Args)
    {
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        SHOKO_STATIC_ASSERT(Meta::HasGUTID<TWidget>,
            "Кажется Вы забыли макрос SHOKO_GENERATED_BODY() внутри класса виджета.\n"
            "Стесняюсь рассказывать Вам всю магию этого макроса, задуманным моим создателем...\n"
            "Просто добавьте макрос SHOKO_GENERATED_BODY() в свой виджет и продолжим!");
        
        return TWidget(Meta::Forward<TArgs>(Args)...);
    }
    
    template<template<typename> class TWidgetWrapper, typename TChildWidget>
    constexpr auto SNew(TChildWidget&& ChildWidget)
    {
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidgetWrapper<TChildWidget>> && Meta::IsWidget<TChildWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        SHOKO_STATIC_ASSERT(Meta::HasGUTID<TWidgetWrapper<TChildWidget>> && Meta::HasGUTID<TChildWidget>,
            "Кажется Вы забыли макрос SHOKO_GENERATED_BODY() внутри класса виджета.\n"
            "Стесняюсь рассказывать Вам всю магию этого макроса, задуманным моим создателем...\n"
            "Просто добавьте макрос SHOKO_GENERATED_BODY() в свой виджет и продолжим!");
        
        return TWidgetWrapper<Meta::Decay<TChildWidget>>(Meta::Forward<TChildWidget>(ChildWidget));
    }
    
    template<template<typename...> class TWidgetContainer, typename... TChildWidgets>
    constexpr auto SNew(TChildWidgets&&... ChildWidgets)
    {
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidgetContainer<Meta::Decay<TChildWidgets>...>> && (Meta::IsWidget<TChildWidgets> && ...),
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        SHOKO_STATIC_ASSERT(Meta::HasGUTID<TWidgetContainer<Meta::Decay<TChildWidgets>...>> && (Meta::HasGUTID<TChildWidgets> && ...),
            "Кажется Вы забыли макрос SHOKO_GENERATED_BODY() внутри класса виджета.\n"
            "Стесняюсь рассказывать Вам всю магию этого макроса, задуманным моим создателем...\n"
            "Просто добавьте макрос SHOKO_GENERATED_BODY() в свой виджет и продолжим!");
        
        return TWidgetContainer<Meta::Decay<TChildWidgets>...>(Meta::Move(ChildWidgets)...);
    }

    // ======== //

    template<typename TWidget>
    constexpr auto SNewAssign(TWidget& OutWidget)
    {
        OutWidget = SNew<TWidget>();
        return OutWidget;
    }
    
    template<typename TWidget, typename... TArgs>
    constexpr auto SNewAssign(TWidget& OutWidget, TArgs&&... Args)
    {
        OutWidget = SNew<TWidget>(Meta::Forward<TArgs>(Args)...);
        return OutWidget;
    }

    template<template<typename> class TWidgetWrapper, typename TChildWidget>
    constexpr auto SNewAssign(TWidgetWrapper<Meta::Decay<TChildWidget>>& OutWidget, TChildWidget&& ChildWidget)
    {
        OutWidget = SNew<TWidgetWrapper>(Meta::Forward<TChildWidget>(ChildWidget));
        return OutWidget;
    }

    template<template<typename...> class TWidgetContainer, typename... TChildWidgets>
    constexpr auto SNewAssign(TWidgetContainer<Meta::Decay<TChildWidgets>...>& OutWidget, TChildWidgets&&... ChildWidgets)
    {
        OutWidget = SNew<TWidgetContainer>(Meta::Move(ChildWidgets)...);
        return OutWidget;
    }
}
