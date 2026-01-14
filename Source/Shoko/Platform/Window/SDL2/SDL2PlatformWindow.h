#pragma once

#include <SDL.h>

#include "Types/Geometry.h"
#include "Types/Color.h"

namespace Shoko
{
    class FShokoSDL2PlatformWindow
    {
#include "../WindowDeclaration.h"
        
    public:
        
        SDL_Renderer* SDLRenderer = nullptr;
    private:
        SDL_Window* SDLWindow = nullptr;
    };
    
    using FShokoPlatformWindow = FShokoSDL2PlatformWindow;
}
