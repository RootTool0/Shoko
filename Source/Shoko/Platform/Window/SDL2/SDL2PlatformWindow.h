#pragma once

#include <SDL.h>

#include "../../../Types/Geometry.h"
#include "../../../Types/Color.h"

namespace Shoko
{
    class FShokoSDL2PlatformWindow
    {
    public:
        bool Initialize();
        void Deinitialize() const;

        void SetTitle(const char* NewTitle) const { SDL_SetWindowTitle(SDLWindow, NewTitle); }
        void SetSize(FUIntVector2D Size) const { SDL_SetWindowSize(SDLWindow, Size.X, Size.Y); }
        
        SDL_Renderer* SDLRenderer = nullptr;
    private:
        SDL_Window* SDLWindow = nullptr;
    };
    
    using FShokoPlatformWindow = FShokoSDL2PlatformWindow;
}
