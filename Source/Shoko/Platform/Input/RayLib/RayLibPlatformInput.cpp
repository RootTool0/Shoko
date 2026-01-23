#include "Config.h"
#include "Types/InputEvent.h"
#if SHOKO_INPUT == SHOKO_INPUT_RayLib

#include "RayLibPlatformInput.h"

#include <raylib.h>

using namespace Shoko;

EKey FShokoRayLibPlatformInput::Key = EKey::None;

bool FShokoRayLibPlatformInput::Initialize() { return IsWindowReady(); }
void FShokoRayLibPlatformInput::Deinitialize() {}

void FShokoRayLibPlatformInput::PullEvents()
{
    if(WindowShouldClose())
    {
        Key = EKey::Window_Close;
        return;
    }
    
    int rawKey = GetKeyPressed();
    if(rawKey != 0) 
    {
        // Простая маскировка под вашу логику A-Z и 0-9
        if (rawKey >= KEY_A && rawKey <= KEY_Z) {
            Key = static_cast<EKey>(rawKey); 
        } else if (rawKey >= KEY_ZERO && rawKey <= KEY_NINE) {
            Key = static_cast<EKey>(rawKey);
        }
    }
    
    if (Key != EKey::None && Key != EKey::Window_Close) {
        if (!IsKeyDown(static_cast<int>(Key))) {
            Key = EKey::None;
        }
    }
}

EKey FShokoRayLibPlatformInput::GetKey() { return Key; }

bool FShokoRayLibPlatformInput::GetLeftShift()  { return IsKeyDown(KEY_LEFT_SHIFT); }
bool FShokoRayLibPlatformInput::GetRightShift() { return IsKeyDown(KEY_RIGHT_SHIFT); }
bool FShokoRayLibPlatformInput::GetLeftAlt()    { return IsKeyDown(KEY_LEFT_ALT); }
bool FShokoRayLibPlatformInput::GetRightAlt()   { return IsKeyDown(KEY_RIGHT_ALT); }
bool FShokoRayLibPlatformInput::GetLeftCtrl()   { return IsKeyDown(KEY_LEFT_CONTROL); }
bool FShokoRayLibPlatformInput::GetRightCtrl()  { return IsKeyDown(KEY_RIGHT_CONTROL); }
bool FShokoRayLibPlatformInput::GetLeftCmd()    { return IsKeyDown(KEY_LEFT_SUPER); }
bool FShokoRayLibPlatformInput::GetRightCmd()   { return IsKeyDown(KEY_RIGHT_SUPER); }

FLocation FShokoRayLibPlatformInput::GetMousePosition()
{
    Vector2 pos = ::GetMousePosition();
    return FLocation(static_cast<int16>(pos.x), static_cast<int16>(pos.y));
}
bool FShokoRayLibPlatformInput::GetMouseLeftButton()   { return IsMouseButtonDown(MOUSE_BUTTON_LEFT); }
bool FShokoRayLibPlatformInput::GetMouseRightButton()  { return IsMouseButtonDown(MOUSE_BUTTON_RIGHT); }
bool FShokoRayLibPlatformInput::GetMouseMiddleButton() { return IsMouseButtonDown(MOUSE_BUTTON_MIDDLE); }

#endif
