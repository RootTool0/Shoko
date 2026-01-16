#pragma once

#include <fstream>

#include "Types/Geometry.h"
#include "Types/Color.h"

namespace Shoko
{
    class FShokoHDMIPlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    private:
        static std::ofstream FrameBuffer;
        static constexpr uint16 ScreenWidth = 1920;
        static constexpr uint16 ScreenHeight = 1080;
    };
    
    using FShokoPlatformRenderer = FShokoHDMIPlatformRenderer;
}
