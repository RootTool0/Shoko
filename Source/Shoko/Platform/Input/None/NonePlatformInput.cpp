#include "Config.h"
#if SHOKO_INPUT == SHOKO_INPUT_NONE

#include "Types/InputEvent.h"
#include "NonePlatformInput.h"

using namespace Shoko;

bool FShokoNonePlatformInput::Initialize() { return true; }
void FShokoNonePlatformInput::Deinitialize() {}

void FShokoNonePlatformInput::PullEvents() {}

EKey FShokoNonePlatformInput::GetKey() { return EKey::None; }

bool FShokoNonePlatformInput::GetLeftShift()  { return false; }
bool FShokoNonePlatformInput::GetRightShift() { return false; }
bool FShokoNonePlatformInput::GetLeftAlt()    { return false; }
bool FShokoNonePlatformInput::GetRightAlt()   { return false; }
bool FShokoNonePlatformInput::GetLeftCtrl()   { return false; }
bool FShokoNonePlatformInput::GetRightCtrl()  { return false; }
bool FShokoNonePlatformInput::GetLeftCmd()    { return false; }
bool FShokoNonePlatformInput::GetRightCmd()   { return false; }

FLocation FShokoNonePlatformInput::GetMousePosition() { return FLocation(0, 0); }
bool FShokoNonePlatformInput::GetMouseLeftButton()   { return false; }
bool FShokoNonePlatformInput::GetMouseRightButton()  { return false; }
bool FShokoNonePlatformInput::GetMouseMiddleButton() { return false; }

#endif
