#pragma once

#include <SDL.h>

#include "Types/Geometry.h"
#include "Types/Color.h"

namespace Shoko
{
    class FShokoSDL2PlatformInput
    {
#include "../InputDeclaration.h"
    };
    
    using FShokoPlatformInput = FShokoSDL2PlatformInput;
}
