#pragma once

#include "Config.h"

#if SHOKO_WINDOW == SHOKO_WINDOW_NONE
#include "Window/None/NonePlatformWindow.h"
#endif

#if SHOKO_WINDOW == SHOKO_WINDOW_SDL2
#include "Window/SDL2/SDL2PlatformWindow.h"
#endif

#if SHOKO_WINDOW == SHOKO_WINDOW_OpenGL
#include "Window/OpenGL/OpenGLPlatformWindow.h"
#endif

#if SHOKO_WINDOW == SHOKO_WINDOW_RayLib
#include "Window/RayLib/RayLibPlatformWindow.h"
#endif

SHOKO_CHECK_ALIAS_EXISTS(FShokoPlatformWindow);
