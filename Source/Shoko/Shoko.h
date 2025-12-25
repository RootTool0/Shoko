#pragma once

#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename TWidget>
    constexpr auto SNew()
    {        
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        return TWidget();
    }
    
    template<typename TWidget, typename... TArgs>
    constexpr auto SNew(TArgs&&... Args)
    {
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        return TWidget(Meta::Forward<TArgs>(Args)...);
    }

    template<template<typename> class TWidgetWrapper, typename TChildWidget>
    constexpr auto SNew(TChildWidget&& ChildWidget)
    {
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TChildWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        return TWidgetWrapper<Meta::Decay<TChildWidget>>(Meta::Forward<TChildWidget>(ChildWidget));
    }

    template<template<typename...> class TWidgetContainer, typename... TChildWidgets>
    constexpr auto SNew(TChildWidgets&&... ChildWidgets)
    {
        SHOKO_STATIC_ASSERT((Meta::IsWidget<TChildWidgets> && ...),
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        return TWidgetContainer<Meta::Decay<TChildWidgets>...>(Meta::Move(ChildWidgets)...);
    }
}
