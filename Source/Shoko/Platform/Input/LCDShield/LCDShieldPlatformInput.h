#pragma once

#include "Core/Aliases.h"
#include "Types/Vector2D.h"

namespace Shoko
{
    class FShokoLCDShieldPlatformInput
    {
#include "../InputDeclaration.h"

    private:
        static int TouchFD;
        static FLocation CurrentPos;
        static bool bIsPressed;
    };
    
    using FShokoPlatformInput = FShokoLCDShieldPlatformInput;
}
