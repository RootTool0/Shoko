#pragma once

#include "Config.h"

#if SHOKO_RENDERER == SHOKO_RENDERER_NONE
#include "Renderer/None/NonePlatformRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2
#include "Renderer/SDL2/SDL2PlatformRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_OpenGL
#include "Renderer/OpenGL/ShokoOpenGLRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_LCDShield
#include "Renderer/LCDShield/LCDShieldPlatformRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_HDMI
#include "Renderer/HDMI/HDMIPlatformRenderer.h"
#endif

#if SHOKO_RENDERER == SHOKO_RENDERER_RayLib
#include "Renderer/RayLib/RayLibPlatformRenderer.h"
#endif

SHOKO_CHECK_ALIAS_EXISTS(FShokoPlatformRenderer);
