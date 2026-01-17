#pragma once

#include "Types/Vector2D.h"
#include "Types/InputEvent.h"
#include "Platform/PlatformInput.h"

namespace Shoko
{
    class FShokoInput
    {
        
    public:
        static bool Initialize() { FShokoPlatformInput::Initialize(); return true; }
        static void Deinitialize() { FShokoPlatformInput::Deinitialize(); }
        
        static FInputEvent PullEvents()
        {
            LastMousePos = CurrentMousePos;
            
            FShokoPlatformInput::PullEvents();
            InputEvent.Key = FShokoPlatformInput::GetKey();
            InputEvent.bLeftShift = FShokoPlatformInput::GetLeftShift();
            InputEvent.bRightShift = FShokoPlatformInput::GetRightShift();
            InputEvent.bLeftAlt = FShokoPlatformInput::GetLeftAlt();
            InputEvent.bRightAlt = FShokoPlatformInput::GetRightAlt();
            InputEvent.bLeftCtrl = FShokoPlatformInput::GetLeftCtrl();
            InputEvent.bRightCtrl = FShokoPlatformInput::GetRightCtrl();
            InputEvent.bLeftCmd = FShokoPlatformInput::GetLeftCmd();
            InputEvent.bRightCmd = FShokoPlatformInput::GetRightCmd();
            
            CurrentMousePos = FShokoPlatformInput::GetMousePos();

            return GetInputEvent();
        }
        
        static constexpr FIntVector2D GetMousePosition() { return CurrentMousePos; }
        static constexpr FIntVector2D GetMouseDelta() { return CurrentMousePos - LastMousePos; }
        
        static constexpr FInputEvent GetInputEvent() { return InputEvent; }
        
    private:
        static FIntVector2D CurrentMousePos;
        static FIntVector2D LastMousePos;
        static FInputEvent InputEvent;
    };
}
