#pragma once

#include "Types/Color.h"

namespace Shoko
{
    struct FStyle
    {
        
    public:
        static constexpr FColor Background          = FColor::FromHex(0x1E1B1DFF);
        static constexpr FColor BackgroundPanel     = FColor::FromHex(0x2C272AFF);
        static constexpr FColor BackgroundPanelDark = FColor::FromHex(0x252124FF);

        static constexpr FColor Border = FColor::FromHex(0x3A3337FF);

        static constexpr FColor Action          = FColor::FromHex(0xC8A3B0FF);
        static constexpr FColor ActionHighlight = FColor::FromHex(0xD6B1BDFF);
        static constexpr FColor ActionDisabled  = FColor::FromHex(0x6C676AFF);
    };
}
