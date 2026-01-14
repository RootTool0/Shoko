#pragma once

#include <fstream>

#include "Types/Geometry.h"
#include "Types/Color.h"

namespace Shoko
{
    class FShokoLCDShieldPlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    private:
        static std::ofstream FrameBuffer;
        static constexpr uint16 ScreenWidth = 320;
        static constexpr uint16 ScreenHeight = 480;
    };
    
    using FShokoPlatformRenderer = FShokoLCDShieldPlatformRenderer;
}
