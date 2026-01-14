#pragma once

#include "Core/Aliases.h"
#include "Widgets/Widget.h"

namespace Shoko
{
    namespace InputManager
    {
        enum class MouseEventType : uint8_t
        {
            Nothing,
            Move,
            OnLeftMouseClick,
            OnRightMouseClick,
            OnMiddleMouseClick
        };
        
        struct MouseEvent
        {
            uint16 X;
            uint16 Y;
            MouseEventType Type;
        };

        SWidget* CurrentWidget;
    }
}
