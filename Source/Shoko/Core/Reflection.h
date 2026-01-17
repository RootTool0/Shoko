#pragma once

#include "Widgets/WidgetBase.h"
#include "Meta.h"

namespace Shoko
{
    namespace Reflection
    {
        template <int ID, typename Func>
        bool TryCallPrivate(const FWidgetBase* Ptr, Func&& InFunc)
        {
            if(Ptr->LocalGUTID != ID) return false;
        
            using WidgetType = decltype(GetClassByGUTID(GUTID_Tag<ID>{}));
            if constexpr (Meta::IsVoid<WidgetType>) return false;
            else InFunc(*reinterpret_cast<const Meta::RemovePointer<WidgetType>*>(Ptr));
        
            return true;
        }
    
        template <typename Func, int... IDs>
        void CallPrivate(const FWidgetBase* Ptr, Func&& InFunc, Meta::IndexSequence<IDs...>) { (TryCallPrivate<IDs>(Ptr, InFunc) || ...); }
    
        template <typename Func>
        void Call(const FWidgetBase* Ptr, Func&& InFunc) { CallPrivate(Ptr, InFunc, Meta::MakeIndexSequence<6>{}); }
    }
}
