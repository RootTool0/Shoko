#pragma once

#include <fstream>

#include "Core/Aliases.h"

#include "Types/Geometry.h"
#include "Types/Color.h"
#include "Types/StaticArray.h"
#include "Types/Renderer.h"
#include "Types/Angle.h"

namespace Shoko
{
    class FShokoLCDShieldPlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    private:
        static uint16_t* BufferPtr;
        static int FBDescriptor;
        
        static constexpr uint16 ScreenWidth  = 480;
        static constexpr uint16 ScreenHeight = 320;
    };
    
#pragma region Polygon
    template <uint8 N> 
    void FShokoLCDShieldPlatformRenderer::DrawPath(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness) {}
#pragma endregion
    
#pragma region Path
    template <uint8 N>
    void FShokoLCDShieldPlatformRenderer::DrawPolygonBorder(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

    using FShokoPlatformRenderer = FShokoLCDShieldPlatformRenderer;
}
