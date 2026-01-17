#include "Config.h"
#if SHOKO_WINDOW == SHOKO_WINDOW_SDL2

#include "SDL2PlatformWindow.h"
#include "Types/Vector2D.h"

#include <iostream>

using namespace Shoko;

bool FShokoSDL2PlatformWindow::Initialize()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << '\n';
        return false;
    }

    SDLWindow = SDL_CreateWindow("[SDL2] Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if(!SDLWindow)
    {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!SDLRenderer)
    {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(SDLWindow);
        SDL_Quit();
        return false;
    }
    
    return true;
}

void FShokoSDL2PlatformWindow::Deinitialize() const
{
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
}

void FShokoSDL2PlatformWindow::SetTitle(const char* NewTitle) const
{
    SDL_SetWindowTitle(SDLWindow, NewTitle);
}
void FShokoSDL2PlatformWindow::SetSize(FUIntVector2D Size) const
{
    SDL_SetWindowSize(SDLWindow, Size.X, Size.Y);
}

#endif
