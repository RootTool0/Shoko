#pragma once

#include SHOKO_PLATFORM_INPUT_INCLUDE
#include "Types/Vector2D.h"
#include "Types/InputEvent.h"

namespace Shoko
{
    class FShokoInput
    {
        
    public:
        static bool Initialize()   { FShokoPlatformInput::Initialize(); return true; }
        static void Deinitialize() { FShokoPlatformInput::Deinitialize(); }
        
        static FInputEvent PullEvents();
        
        static bool IsMouseDown(EMouseButton Button)        { return  (CurrentMouseButtonsState & static_cast<uint8>(Button)) != 0; }
        static bool IsMouseWasPressed(EMouseButton Button)  { return  (CurrentMouseButtonsState & static_cast<uint8>(Button)) && !(LastMouseButtonsState & static_cast<uint8>(Button));  }
        static bool IsMouseWasReleased(EMouseButton Button) { return !(CurrentMouseButtonsState & static_cast<uint8>(Button)) &&  (LastMouseButtonsState & static_cast<uint8>(Button));  }
        
        static bool HasModifier(EModifier Mask) { return (InputEvent.Modifiers & static_cast<uint8>(Mask)) != 0; }

        static FLocation GetMousePosition() { return CurrentMousePosition; }
        static FLocation GetMouseDelta() { return CurrentMousePosition - LastMousePosition; }
        
        static FInputEvent GetInputEvent() { return InputEvent; }
        
    private:
        static FLocation CurrentMousePosition;
        static FLocation LastMousePosition;
        
        static uint8 CurrentMouseButtonsState;
        static uint8 LastMouseButtonsState;
        
        static FInputEvent InputEvent;
    };
}
