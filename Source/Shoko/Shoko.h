#pragma once

#include "Core/Meta.h"
#include "Core/New.h"
#include "Widgets.h"
#include "Window.h"
#include "Input.h"
#include "Types/Angle.h"
#include "Types/StaticArray.h"

namespace Shoko
{
    template<typename TWidget>
    constexpr const TWidget* Cast(const FWidgetBase* InPointer)
    {
        SHOKO_STATIC_ASSERT(Meta::IsWidget<TWidget>,
            "Кажется Вы пытаетесь создать виджет, о котором я не знаю...\n"
            "Скорее всего он просто не унаследован от базового класса SWidget\n"
            "Может, расскажете мне, что это за виджет?");
        
        SHOKO_STATIC_ASSERT(Meta::HasGUTID<TWidget>,
            "Кажется Вы забыли макрос SHOKO_GENERATED_BODY() внутри класса виджета.\n"
            "Стесняюсь рассказывать Вам всю магию этого макроса, задуманным моим создателем...\n"
            "Просто добавьте макрос SHOKO_GENERATED_BODY() в свой виджет и продолжим!");
        
        return InPointer && InPointer->LocalGUTID == TWidget::StaticGUTID ? static_cast<const TWidget*>(InPointer) : nullptr;
    }
}

#include "Core/Reflection.h"
