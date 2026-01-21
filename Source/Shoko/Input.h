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
            LastMousePosition = CurrentMousePosition;
            LastMouseButtonsState = CurrentMouseButtonsState;
            
            FShokoPlatformInput::PullEvents();
            InputEvent.Key = FShokoPlatformInput::GetKey();
            CurrentMousePosition = FShokoPlatformInput::GetMousePosition();
            
            InputEvent.Modifiers = 0;
            if(FShokoPlatformInput::GetLeftShift())  InputEvent.Modifiers |= static_cast<uint8>(EModifier::LeftShift);
            if(FShokoPlatformInput::GetRightShift()) InputEvent.Modifiers |= static_cast<uint8>(EModifier::RightShift);
            if(FShokoPlatformInput::GetLeftCtrl())   InputEvent.Modifiers |= static_cast<uint8>(EModifier::LeftCtrl);
            if(FShokoPlatformInput::GetRightCtrl())  InputEvent.Modifiers |= static_cast<uint8>(EModifier::RightCtrl);
            if(FShokoPlatformInput::GetLeftAlt())    InputEvent.Modifiers |= static_cast<uint8>(EModifier::LeftAlt);
            if(FShokoPlatformInput::GetRightAlt())   InputEvent.Modifiers |= static_cast<uint8>(EModifier::RightAlt);
            if(FShokoPlatformInput::GetLeftCmd())    InputEvent.Modifiers |= static_cast<uint8>(EModifier::LeftCmd);
            if(FShokoPlatformInput::GetRightCmd())   InputEvent.Modifiers |= static_cast<uint8>(EModifier::RightCmd);

            CurrentMouseButtonsState = 0;
            if(FShokoPlatformInput::GetMouseLeftButton())   CurrentMouseButtonsState |= static_cast<uint8>(EMouseButton::Left);
            if(FShokoPlatformInput::GetMouseRightButton())  CurrentMouseButtonsState |= static_cast<uint8>(EMouseButton::Right);
            if(FShokoPlatformInput::GetMouseMiddleButton()) CurrentMouseButtonsState |= static_cast<uint8>(EMouseButton::Middle);
            
            return GetInputEvent();
        }
        
        static bool IsMouseDown(EMouseButton Button)        { return  (CurrentMouseButtonsState & static_cast<uint8>(Button)) != 0; }
        static bool IsMouseWasPressed(EMouseButton Button)  { return  (CurrentMouseButtonsState & static_cast<uint8>(Button)) && !(LastMouseButtonsState & static_cast<uint8>(Button));  }
        static bool IsMouseWasReleased(EMouseButton Button) { return !(CurrentMouseButtonsState & static_cast<uint8>(Button)) &&  (LastMouseButtonsState & static_cast<uint8>(Button));  }
        
        static bool HasModifier(EModifier Mask) { return (InputEvent.Modifiers & static_cast<uint8>(Mask)) != 0; }

        static constexpr FIntVector2D GetMousePosition() { return CurrentMousePosition; }
        static constexpr FIntVector2D GetMouseDelta() { return CurrentMousePosition - LastMousePosition; }
        
        static constexpr FInputEvent GetInputEvent() { return InputEvent; }
        
    private:
        static FIntVector2D CurrentMousePosition;
        static FIntVector2D LastMousePosition;
        
        static uint8 CurrentMouseButtonsState;
        static uint8 LastMouseButtonsState;
        
        static FInputEvent InputEvent;
    };
}
