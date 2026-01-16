#include "Config.h"
#if SHOKO_WINDOW == SHOKO_WINDOW_NONE
#include "NonePlatformWindow.h"

using namespace Shoko;

bool FShokoNonePlatformWindow::Initialize() { return true; }
void FShokoNonePlatformWindow::Deinitialize() const {}

void FShokoNonePlatformWindow::SetTitle(const char* NewTitle) const {}
void FShokoNonePlatformWindow::SetSize(FUIntVector2D Size) const {}

#endif
