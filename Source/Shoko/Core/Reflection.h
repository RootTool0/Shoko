#pragma once

#include "Widgets/WidgetBase.h"
#include "Meta.h"

namespace Shoko
{
    namespace Reflection
    {
        template<GUTID InGUTID>
        auto GetClassByGUTID() { return GetClassByGUTIDPrivate(GUTIDReflectionFlag<InGUTID>{}); }  // NOLINT(clang-diagnostic-class-varargs)
        
        template<GUTID InGUTID, typename Func>
        bool TryCallPrivate(const FWidgetBase* Ptr, Func&& InFunc)
        {
            if(Ptr->LocalGUTID != InGUTID) return false;
        
            using WidgetType = decltype(GetClassByGUTID<InGUTID>());
            if constexpr (Meta::IsVoid<WidgetType>) return false;
            else InFunc(*reinterpret_cast<const Meta::RemovePointer<WidgetType>*>(Ptr));
        
            return true;
        }
        
        template<typename Func, GUTID... InGUTIDs>
        void CallPrivate(const FWidgetBase* Ptr, Func&& InFunc, Meta::IndexSequence<InGUTIDs...>) { (TryCallPrivate<InGUTIDs>(Ptr, InFunc) || ...); }
    
        template<typename Func>
        void Call(const FWidgetBase* Ptr, Func&& InFunc) { CallPrivate(Ptr, InFunc, Meta::MakeIndexSequence<6>{}); }
    }
}
