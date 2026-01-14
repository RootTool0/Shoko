#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    class FWidgetBase
    {
    public:
        GUTID_t LocalGUTID = 0;

        constexpr FWidgetBase(GUTID_t InGUTID) : LocalGUTID(InGUTID) {}
    };
}
