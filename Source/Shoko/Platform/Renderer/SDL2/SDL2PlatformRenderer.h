#pragma once

#include <SDL.h>

#include "../../../Types/Geometry.h"
#include "../../../Types/Color.h"

namespace Shoko
{
    class FShokoSDL2PlatformRenderer
    {
    public:
        // static bool MainLoop();
        static void PreRender();
        static void PostRender();
        
        static void DrawRect(FGeometry Geometry, FColor Color);
        
        static SDL_Renderer* SDLRenderer;
    };
    
    using FShokoPlatformRenderer = FShokoSDL2PlatformRenderer;
}
