#pragma once

#include <fstream>

#include "../../../Types/Geometry.h"
#include "../../../Types/Color.h"

namespace Shoko
{
    class FShokoLCDShieldPlatformRenderer
    {
    public:
        static bool Initialize();
        static void Deinitialize();
        
        static void PreRender();
        static void PostRender();
        
        static void Fill(FColor Color);
        static void DrawRect(FGeometry Geometry, FColor Color);

    private:
        static std::ofstream FrameBuffer;
        static constexpr uint16 ScreenWidth = 320;
        static constexpr uint16 ScreenHeight = 480;
    };
    
    using FShokoPlatformRenderer = FShokoLCDShieldPlatformRenderer;
}
