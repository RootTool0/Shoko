#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    template<GUTID_t GUTID> struct GUTID_Tag {};
    void GetClassByGUTID(...);
    
    class FWidgetBase
    {
    public:
        GUTID_t LocalGUTID = 0;

        constexpr FWidgetBase(GUTID_t InGUTID) : LocalGUTID(InGUTID) {}
    };
}
