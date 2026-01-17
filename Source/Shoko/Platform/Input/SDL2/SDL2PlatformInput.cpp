#include "Config.h"
#include "Types/InputEvent.h"
#if SHOKO_INPUT == SHOKO_INPUT_SDL2

#include "SDL2PlatformInput.h"

using namespace Shoko;

SDL_Keymod FShokoSDL2PlatformInput::CurrentKeyMod = KMOD_NONE;
EKey FShokoSDL2PlatformInput::Key = EKey::None;

bool FShokoSDL2PlatformInput::Initialize() { return SDL_WasInit(SDL_INIT_VIDEO) != 0; }
void FShokoSDL2PlatformInput::Deinitialize() {}

void FShokoSDL2PlatformInput::PullEvents()
{
    // Key = EKey::None;
    CurrentKeyMod = SDL_GetModState();
    
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
        switch (Event.type)
        {
        default: break;
        case SDL_QUIT: Key = EKey::Window_Close; break;
        case SDL_KEYUP: case SDL_MOUSEBUTTONUP: Key = EKey::None; break;
        case SDL_KEYDOWN:
            {
                const SDL_Keycode& KeyCode = Event.key.keysym.sym;
                if(KeyCode >= SDLK_a && KeyCode <= SDLK_z) { Key = static_cast<EKey>(KeyCode - ('a' - 'A')); break; }
                if(KeyCode >= SDLK_0 && KeyCode <= SDLK_9) { Key = static_cast<EKey>(KeyCode); break; }
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                switch (Event.button.button)
                {
                default: break;
                case SDL_BUTTON_LEFT:   Key = EKey::Mouse_Left;   break;
                case SDL_BUTTON_RIGHT:  Key = EKey::Mouse_Right;  break;
                case SDL_BUTTON_MIDDLE: Key = EKey::Mouse_Middle; break;
                }
                break;
            }
        }
    }
}

EKey FShokoSDL2PlatformInput::GetKey() { return Key; }

bool FShokoSDL2PlatformInput::GetLeftShift()  { return (CurrentKeyMod & KMOD_LSHIFT) != 0; }
bool FShokoSDL2PlatformInput::GetRightShift() { return (CurrentKeyMod & KMOD_RSHIFT) != 0; }
bool FShokoSDL2PlatformInput::GetLeftAlt()    { return (CurrentKeyMod & KMOD_LALT) != 0; }
bool FShokoSDL2PlatformInput::GetRightAlt()   { return (CurrentKeyMod & KMOD_RALT) != 0; }
bool FShokoSDL2PlatformInput::GetLeftCtrl()   { return (CurrentKeyMod & KMOD_LCTRL) != 0; }
bool FShokoSDL2PlatformInput::GetRightCtrl()  { return (CurrentKeyMod & KMOD_RCTRL) != 0; }
bool FShokoSDL2PlatformInput::GetLeftCmd()    { return (CurrentKeyMod & KMOD_LGUI) != 0; }
bool FShokoSDL2PlatformInput::GetRightCmd()   { return (CurrentKeyMod & KMOD_RGUI) != 0; }

FIntVector2D FShokoSDL2PlatformInput::GetMousePos()
{
    int X, Y;
    SDL_GetMouseState(&X, &Y);
    return FIntVector2D(static_cast<int16>(X), static_cast<int16>(Y));
}

#endif
