#pragma once

#include <SDL.h>

#include "../../../Types/Geometry.h"
#include "../../../Types/Color.h"

namespace Shoko
{
    class FShokoSDL2Renderer
    {
    public:
        static bool Initialize();
        static void Deinitialize();

        static bool MainLoop();
        static void PreRender();
        static void PostRender();
        
        static void DrawRect(FGeometry Geometry, FColor Color);
        
    private:
        static SDL_Window* SDLWindow;
        static SDL_Renderer* SDLRenderer;
        static bool bRunning;
    };
    
    using FShokoRenderer = FShokoSDL2Renderer;
}
