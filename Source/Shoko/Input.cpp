#include "Input.h"

using namespace Shoko;

FLocation FShokoInput::CurrentMousePosition = FLocation(0, 0);
FLocation FShokoInput::LastMousePosition    = FLocation(0, 0);

uint8 FShokoInput::CurrentMouseButtonsState = 0;
uint8 FShokoInput::LastMouseButtonsState = 0;
        
FInputEvent FShokoInput::InputEvent = FInputEvent();

FInputEvent FShokoInput::PullEvents()
{
    LastMousePosition = CurrentMousePosition;
    LastMouseButtonsState = CurrentMouseButtonsState;
            
    FShokoPlatformInput::PullEvents();
    CurrentMousePosition = FShokoPlatformInput::GetMousePosition();
    
    uint8 NewKey = FShokoPlatformInput::GetKey();
    InputEvent.bRepeat = NewKey == InputEvent.Key;
    InputEvent.Key = NewKey;
    
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
