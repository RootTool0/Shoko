#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    template<GUTID InGUTID> struct GUTIDReflectionFlag {};
    void GetClassByGUTIDPrivate(...);
    
    class FWidgetBase
    {
        
    public:
        GUTID LocalGUTID = 0;

        constexpr FWidgetBase(GUTID InGUTID) : LocalGUTID(InGUTID) {}
    };
}
