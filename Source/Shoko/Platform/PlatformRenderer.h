#pragma once

#include "../Config.h"

#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2
#include "Renderer/SDL2/SDL2PlatformRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_OpenGL
#include "Renderer/OpenGL/ShokoOpenGLRenderer.h"
#endif
