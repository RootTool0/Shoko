#pragma once

#include <SDL.h>

#include "Types/Vector2D.h"

namespace Shoko
{
    class FShokoSDL2PlatformInput
    {
#include "../InputDeclaration.h"

    private:
        static SDL_Keymod CurrentKeyMod;
        static EKey Key;
    };
    
    using FShokoPlatformInput = FShokoSDL2PlatformInput;
}
