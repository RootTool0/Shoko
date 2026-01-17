#include "Input.h"

using namespace Shoko;


FIntVector2D FShokoInput::CurrentMousePos = FIntVector2D(0, 0);
FIntVector2D FShokoInput::LastMousePos = FIntVector2D(0, 0);
FInputEvent FShokoInput::InputEvent = FInputEvent();
