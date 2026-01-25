#include "LCDShieldPlatformInput.h"

using namespace Shoko;

bool FShokoLCDShieldPlatformInput::Initialize() { return true; }
void FShokoLCDShieldPlatformInput::Deinitialize() {}
void FShokoLCDShieldPlatformInput::PullEvents() {}

uint8 FShokoLCDShieldPlatformInput::GetKey() { return 0; }

bool FShokoLCDShieldPlatformInput::GetLeftShift()  { return false; }
bool FShokoLCDShieldPlatformInput::GetRightShift() { return false; }
bool FShokoLCDShieldPlatformInput::GetLeftAlt()    { return false; }
bool FShokoLCDShieldPlatformInput::GetRightAlt()   { return false; }
bool FShokoLCDShieldPlatformInput::GetLeftCtrl()   { return false; }
bool FShokoLCDShieldPlatformInput::GetRightCtrl()  { return false; }
bool FShokoLCDShieldPlatformInput::GetLeftCmd()    { return false; }
bool FShokoLCDShieldPlatformInput::GetRightCmd()   { return false; }

FLocation FShokoLCDShieldPlatformInput::GetMousePosition() { return FLocation(0, 0); }
bool FShokoLCDShieldPlatformInput::GetMouseLeftButton()    { return false; }
bool FShokoLCDShieldPlatformInput::GetMouseRightButton()   { return false; }
bool FShokoLCDShieldPlatformInput::GetMouseMiddleButton()  { return false; }
