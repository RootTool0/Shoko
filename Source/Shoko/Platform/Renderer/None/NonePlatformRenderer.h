#pragma once

#include "Types/Renderer.h"
#include "Types/StaticArray.h"

namespace Shoko
{
    struct FAngle;
    
    class FShokoNonePlatformRenderer
    {
#include "../RendererDeclaration.h"
    };
    
    template <uint8 N> void FShokoNonePlatformRenderer::DrawPath(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness) {} 
    template <uint8 N> void FShokoNonePlatformRenderer::DrawPolygonBorder(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
    
    using FShokoPlatformRenderer = FShokoNonePlatformRenderer;
}
