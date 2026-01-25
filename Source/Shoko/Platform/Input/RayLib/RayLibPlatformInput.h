#pragma once

#include "Types/Vector2D.h"

namespace Shoko
{
    class FShokoRayLibPlatformInput
    {
#include "../InputDeclaration.h"

    private:
        static uint8 Key;
    };
    
    using FShokoPlatformInput = FShokoRayLibPlatformInput;
}
