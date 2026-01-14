#pragma once

#include <SDL.h>

#include "Types/Geometry.h"
#include "Types/Color.h"

namespace Shoko
{
    class FShokoSDL2PlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    public:
        // static bool MainLoop();
        static SDL_Renderer* SDLRenderer;
    };
    
    using FShokoPlatformRenderer = FShokoSDL2PlatformRenderer;
}
