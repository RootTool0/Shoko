#include "RayLibPlatformInput.h"
#include "Types/InputEvent.h"

#include <raylib.h>

using namespace Shoko;

uint8 FShokoRayLibPlatformInput::Key = 0;

bool FShokoRayLibPlatformInput::Initialize() { return IsWindowReady(); }
void FShokoRayLibPlatformInput::Deinitialize() {}

void FShokoRayLibPlatformInput::PullEvents()
{
    if(WindowShouldClose())
    {
        Key = FInputEvent::GetKey(ESystemKey::Window_Close);
        return;
    }
    
    int RawKey = GetKeyPressed();
    if(RawKey != 0) 
    {
        if ((KEY_A <= RawKey && RawKey <= KEY_Z) || (KEY_ZERO <= RawKey && RawKey <= KEY_NINE)) 
            Key = FInputEvent::GetKey(static_cast<EKeyboardKey>(RawKey)); 
        else if (RawKey == KEY_BACKSPACE)
            Key = FInputEvent::GetKey(EKeyboardKey::Special_Backspace); 
        else if (RawKey == KEY_SPACE)
            Key = FInputEvent::GetKey(EKeyboardKey::Special_Space);
        else if (RawKey == KEY_PERIOD)
            Key = FInputEvent::GetKey(EKeyboardKey::Special_Period);
        else if (RawKey == KEY_COMMA)
            Key = FInputEvent::GetKey(EKeyboardKey::Special_Comma);
        else if (RawKey == KEY_SEMICOLON)
            Key = FInputEvent::GetKey(EKeyboardKey::Special_Semicolon);
        
        return;
    }

    Key = 0;
}

uint8 FShokoRayLibPlatformInput::GetKey() { return Key; }

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
