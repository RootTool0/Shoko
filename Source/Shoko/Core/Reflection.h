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
        bool TryCallWidgetPrivate(const FWidgetBase* Ptr, Func&& InFunc)
        {
            if(Ptr->LocalGUTID != InGUTID) return false;
        
            using WidgetType = decltype(GetClassByGUTID<InGUTID>());
            
            if constexpr (Meta::IsVoid<WidgetType>) return false;
            else InFunc(*reinterpret_cast<const Meta::RemovePointer<WidgetType>*>(Ptr));
        
            return true;
        }
        
        template<typename Func, GUTID... InGUTIDs>
        void ForEachWidgetPrivate(const FWidgetBase* Ptr, Func&& InFunc, Meta::IndexSequence<InGUTIDs...>) { (TryCallWidgetPrivate<InGUTIDs>(Ptr, InFunc) || ...); }
    
        template<typename Func>
        void ForEachWidget(const FWidgetBase* Ptr, Func&& InFunc) { ForEachWidgetPrivate(Ptr, InFunc, Meta::MakeIndexSequence<__COUNTER__>{}); }
        
        template <typename T, typename Func> constexpr bool HasMethod(Func&&) { return Meta::HasMethod<T, Func>::Value; }
        // template <typename T, typename Func> constexpr void TryCall(T& Obj, Func&& InFunc) { if constexpr (Meta::HasMethod<T, Func>::Value) InFunc(Obj); }
    }
}
