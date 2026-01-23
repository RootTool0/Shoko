#include "Input.h"

using namespace Shoko;

FLocation FShokoInput::CurrentMousePosition = FLocation(0, 0);
FLocation FShokoInput::LastMousePosition    = FLocation(0, 0);

uint8 FShokoInput::CurrentMouseButtonsState = 0;
uint8 FShokoInput::LastMouseButtonsState = 0;
        
FInputEvent FShokoInput::InputEvent = FInputEvent();
