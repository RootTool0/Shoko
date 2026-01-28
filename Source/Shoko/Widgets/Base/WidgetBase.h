#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    /*
    template<GUTID InGUTID> struct GUTIDReflectionFlag {};
    void GetClassByGUTIDPrivate(...);
    */

    template<GUTID InGUTID>
    struct TClassByGUTIDPrivate { using Type = void; };
    
    class FWidgetBase
    {
        
    public:
        GUTID LocalGUTID = 0;

        constexpr FWidgetBase(GUTID InGUTID) : LocalGUTID(InGUTID) {}
    };
}
