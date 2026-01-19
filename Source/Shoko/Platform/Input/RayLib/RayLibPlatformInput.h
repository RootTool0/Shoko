#pragma once

#include <raylib.h>

#include "Types/Vector2D.h"

namespace Shoko
{
    enum class EKey : uint8;

    class FShokoRayLibPlatformInput
    {
#include "../InputDeclaration.h"

    private:
        static EKey Key;
    };
    
    using FShokoPlatformInput = FShokoRayLibPlatformInput;
}
