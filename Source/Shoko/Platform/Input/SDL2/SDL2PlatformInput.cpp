#include "Config.h"
#include "Types/InputEvent.h"
#if SHOKO_INPUT == SHOKO_INPUT_SDL2

#include "SDL2PlatformInput.h"

using namespace Shoko;

SDL_Keymod FShokoSDL2PlatformInput::Keymod = KMOD_NONE;
EKey FShokoSDL2PlatformInput::Key = EKey::None;
int FShokoSDL2PlatformInput::MouseX = 0;
int FShokoSDL2PlatformInput::MouseY = 0;
uint32 FShokoSDL2PlatformInput::MouseMask = 0;

bool FShokoSDL2PlatformInput::Initialize() { return SDL_WasInit(SDL_INIT_VIDEO) != 0; }
void FShokoSDL2PlatformInput::Deinitialize() {}

void FShokoSDL2PlatformInput::PullEvents()
{
    Keymod = SDL_GetModState();
    MouseMask = SDL_GetMouseState(&MouseX, &MouseY);
    
    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
        switch (Event.type)
        {
        default: break;
        case SDL_QUIT: Key = EKey::Window_Close; break;
        case SDL_KEYUP: Key = EKey::None; break;
        case SDL_KEYDOWN:
            {
                const SDL_Keycode& KeyCode = Event.key.keysym.sym;
                if(KeyCode >= SDLK_a && KeyCode <= SDLK_z) { Key = static_cast<EKey>(KeyCode - ('a' - 'A')); break; }
                if(KeyCode >= SDLK_0 && KeyCode <= SDLK_9) { Key = static_cast<EKey>(KeyCode); break; }
                break;
            }
        }
    }
}

EKey FShokoSDL2PlatformInput::GetKey() { return Key; }

bool FShokoSDL2PlatformInput::GetLeftShift()  { return (Keymod & KMOD_LSHIFT) != 0; }
bool FShokoSDL2PlatformInput::GetRightShift() { return (Keymod & KMOD_RSHIFT) != 0; }
bool FShokoSDL2PlatformInput::GetLeftAlt()    { return (Keymod & KMOD_LALT) != 0; }
bool FShokoSDL2PlatformInput::GetRightAlt()   { return (Keymod & KMOD_RALT) != 0; }
bool FShokoSDL2PlatformInput::GetLeftCtrl()   { return (Keymod & KMOD_LCTRL) != 0; }
bool FShokoSDL2PlatformInput::GetRightCtrl()  { return (Keymod & KMOD_RCTRL) != 0; }
bool FShokoSDL2PlatformInput::GetLeftCmd()    { return (Keymod & KMOD_LGUI) != 0; }
bool FShokoSDL2PlatformInput::GetRightCmd()   { return (Keymod & KMOD_RGUI) != 0; }

FLocation FShokoSDL2PlatformInput::GetMousePosition()
{
    int X, Y;
    SDL_GetMouseState(&X, &Y);
    return FLocation(static_cast<int16>(X), static_cast<int16>(Y));
}
bool FShokoSDL2PlatformInput::GetMouseLeftButton()   { return (MouseMask & SDL_BUTTON_LMASK) != 0; }
bool FShokoSDL2PlatformInput::GetMouseRightButton()  { return (MouseMask & SDL_BUTTON_RMASK) != 0; }
bool FShokoSDL2PlatformInput::GetMouseMiddleButton() { return (MouseMask & SDL_BUTTON_MMASK) != 0; }

#endif
