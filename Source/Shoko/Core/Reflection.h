#pragma once

#include "Widgets/WidgetBase.h"
#include "Meta.h"

namespace Shoko
{
    namespace Reflection
    {
        /*
        template<GUTID InGUTID>
        auto GetClassByGUTID() { return GetClassByGUTIDPrivate(GUTIDReflectionFlag<InGUTID>{}); }  // NOLINT(clang-diagnostic-class-varargs)
        */
        
        template<GUTID InGUTID>
        auto GetClassByGUTID() 
        {
            using FoundType = typename TClassByGUTIDPrivate<InGUTID>::Type;
            
            if constexpr (Meta::IsVoid<FoundType>) return static_cast<void*>(nullptr);
            else return static_cast<FoundType*>(nullptr);
        }
        
        template<GUTID InGUTID, typename Func>
        bool TryCallMethod(const FWidgetBase* Ptr, Func&& InFunc)
        {
            using FoundType = typename TClassByGUTIDPrivate<InGUTID>::Type;
            
            if constexpr (!Meta::IsVoid<FoundType>) 
            {
                if(Ptr->LocalGUTID != InGUTID) return false;

                const FoundType* TypedWidget = static_cast<const FoundType*>(Ptr);
                if(!TypedWidget) return false;
                
                InFunc(*TypedWidget); 
                return true;
            }
            
            else return false;
        }
        
        template<typename Func, auto... InGUTIDs>
        void ForEachWidgetPrivate(const FWidgetBase* Ptr, Func&& InFunc, Meta::IndexSequence<InGUTIDs...>) { (TryCallMethod<InGUTIDs>(Ptr, InFunc) || ...); }
        
        template<typename Func>
        void ForEachWidget(const FWidgetBase* Ptr, Func&& InFunc) { ForEachWidgetPrivate(Ptr, InFunc, Meta::MakeIndexSequence<__COUNTER__>{}); }
        
        template <typename T, typename Func> constexpr bool HasMember(Func&&) { return Meta::HasMember<T, Func>::Value; }
        
        // template <typename T, typename Func> constexpr void TryCall(T& Obj, Func&& InFunc) { if constexpr (Meta::HasMethod<T, Func>::Value) InFunc(Obj); }
    }
}
