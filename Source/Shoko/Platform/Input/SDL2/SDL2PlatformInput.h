#pragma once

#include <SDL.h>

#include "Types/Vector2D.h"

namespace Shoko
{
    class FShokoSDL2PlatformInput
    {
#include "../InputDeclaration.h"

    private:
        static SDL_Keymod Keymod;
        static EKey Key;
        static int MouseX, MouseY;
        static uint32 MouseMask;
    };
    
    using FShokoPlatformInput = FShokoSDL2PlatformInput;
}
