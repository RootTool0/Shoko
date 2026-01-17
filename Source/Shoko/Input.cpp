#include "Input.h"

using namespace Shoko;

FIntVector2D FShokoInput::CurrentMousePosition = FIntVector2D(0, 0);
FIntVector2D FShokoInput::LastMousePosition = FIntVector2D(0, 0);

uint8 FShokoInput::CurrentMouseButtonsState = 0;
uint8 FShokoInput::LastMouseButtonsState = 0;
        
FInputEvent FShokoInput::InputEvent = FInputEvent();
