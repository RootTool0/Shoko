#include "ShokoSDL2Renderer.h"

#include <iostream>

using namespace Shoko;

SDL_Window* FShokoSDL2Renderer::SDLWindow = nullptr;
SDL_Renderer* FShokoSDL2Renderer::SDLRenderer = nullptr;
bool FShokoSDL2Renderer::bRunning = true;

bool FShokoSDL2Renderer::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << '\n';
        return false;
    }

    SDLWindow = SDL_CreateWindow("Hi, Shoko! SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!SDLWindow)
    {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!SDLRenderer)
    {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(SDLWindow);
        SDL_Quit();
        return false;
    }
    
    return true;
}

void FShokoSDL2Renderer::Deinitialize()
{
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
}

bool FShokoSDL2Renderer::MainLoop()
{
    SDL_Event SDLEvent;
    while(SDL_PollEvent(&SDLEvent))
        if(SDLEvent.type == SDL_QUIT) return false;
    return true;
}

void FShokoSDL2Renderer::PreRender()
{
    SDL_SetRenderDrawColor(SDLRenderer, 30, 30, 120, 255);
    SDL_RenderClear(SDLRenderer);
}

void FShokoSDL2Renderer::PostRender()
{
    SDL_RenderPresent(SDLRenderer);
}

void FShokoSDL2Renderer::DrawRect(FGeometry Geometry, FColor Color)
{
    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);
    SDL_Rect Rect = {Geometry.Location.X, Geometry.Location.Y, Geometry.Size.X, Geometry.Size.Y};
    SDL_RenderFillRect(SDLRenderer, &Rect);
}
