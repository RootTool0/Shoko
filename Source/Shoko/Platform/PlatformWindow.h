#pragma once

#include "Config.h"

#if SHOKO_WINDOW == SHOKO_WINDOW_NONE
#include "Window/None/None.h"
#endif

#if SHOKO_WINDOW == SHOKO_WINDOW_SDL2
#include "Window/SDL2/SDL2PlatformWindow.h"
#endif

/*
#if SHOKO_WINDOW == SHOKO_WINDOW_OpenGL
#include "Backends/OpenGL/ShokoOpenGLWindow.h"
#endif
*/

SHOKO_CHECK_ALIAS_EXISTS(FShokoPlatformWindow);
