#pragma once

#include "Config.h"
#include "Core/Macros.h"

#if SHOKO_INPUT == SHOKO_INPUT_NONE
#include "Input/None/None.h"
#endif

#if SHOKO_INPUT == SHOKO_INPUT_SDL2
#include "Input/SDL2/SDL2PlatformInput.h"
#endif

SHOKO_CHECK_ALIAS_EXISTS(FShokoPlatformInput);
