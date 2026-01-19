#pragma once

#include <raylib.h>

#include "Types/Geometry.h"
#include "Types/Color.h"

namespace Shoko
{
    class FShokoSDL2PlatformWindow
    {
#include "../WindowDeclaration.h"
    };
    
    using FShokoPlatformWindow = FShokoSDL2PlatformWindow;
}
