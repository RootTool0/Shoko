#pragma once

#include "Types/Vector2D.h"

namespace Shoko
{
    enum class EKey : uint8;

    class FShokoNonePlatformInput
    {
#include "../InputDeclaration.h"
    };
    
    using FShokoPlatformInput = FShokoNonePlatformInput;
}
