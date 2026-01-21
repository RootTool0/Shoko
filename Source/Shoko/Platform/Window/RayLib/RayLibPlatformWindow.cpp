#include "Config.h"
#include "Window.h"
#if SHOKO_WINDOW == SHOKO_WINDOW_RayLib

#include "RayLibPlatformWindow.h"
#include "Types/Vector2D.h"

#include <raylib.h>
#include <iostream>

using namespace Shoko;

bool FShokoSDL2PlatformWindow::Initialize()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT); 
    
    InitWindow(800, 600, "[RayLib] Window");

    if(!IsWindowReady())
    {
        std::cerr << "RayLib InitWindow error: Не удалось создать окно или контекст OpenGL\n";
        return false;
    }

    return true;
}

void FShokoSDL2PlatformWindow::Deinitialize() const
{
    CloseWindow();
}

void FShokoSDL2PlatformWindow::SetTitle(const char* NewTitle) const
{
    SetWindowTitle(NewTitle);
}
void FShokoSDL2PlatformWindow::SetSize(FUIntVector2D Size) const
{
    SetWindowSize(static_cast<int>(Size.X), static_cast<int>(Size.Y));
}

#endif
