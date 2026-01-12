#include "../../../Config.h"
#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2

#include "SDL2PlatformRenderer.h"

#include <iostream>

using namespace Shoko;

SDL_Renderer* FShokoSDL2PlatformRenderer::SDLRenderer = nullptr;

/*
bool FShokoSDL2PlatformRenderer::MainLoop()
{
    SDL_Event SDLEvent;
    while(SDL_PollEvent(&SDLEvent))
        if(SDLEvent.type == SDL_QUIT) return false;
    return true;
}
*/

void FShokoSDL2PlatformRenderer::PreRender()
{
    if(!SDLRenderer) return;
    
    SDL_Event event;
    SDL_SetRenderDrawColor(SDLRenderer, 30, 30, 120, 255);
    SDL_RenderClear(SDLRenderer);
}

void FShokoSDL2PlatformRenderer::PostRender()
{
    if(!SDLRenderer) return;
    
    SDL_RenderPresent(SDLRenderer);
}

void FShokoSDL2PlatformRenderer::DrawRect(FGeometry Geometry, FColor Color)
{
    if(!SDLRenderer) return;
    
    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);
    SDL_Rect Rect = {Geometry.Location.X, Geometry.Location.Y, Geometry.Size.X, Geometry.Size.Y};
    SDL_RenderFillRect(SDLRenderer, &Rect);
}

#endif
