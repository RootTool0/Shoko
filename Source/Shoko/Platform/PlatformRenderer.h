#pragma once

#include "../Config.h"
// #include "../Core/Meta.h"

#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2
#include "Renderer/SDL2/SDL2PlatformRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_OpenGL
#include "Renderer/OpenGL/ShokoOpenGLRenderer.h"
#endif

SHOKO_CHECK_ALIAS_EXISTS(FShokoPlatformRenderer);
