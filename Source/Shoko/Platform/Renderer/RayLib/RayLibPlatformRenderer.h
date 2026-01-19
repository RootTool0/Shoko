#pragma once

#include <raylib.h>

#undef PI
#undef DEG2RAD
#undef RAD2DEG

#include "Core/Aliases.h"
#include "Types/Color.h"
#include "Types/StaticArray.h"
#include "Types/Renderer.h"
#include "Types/Vector2D.h"

namespace Shoko
{
    struct FAngle;
    
#define TO_RL_COLOR(c) { c.R, c.G, c.B, c.A }
#define TO_RL_V2(l) { (float)l.X, (float)l.Y }

    class FShokoRayLibPlatformRenderer
    {
#include "../RendererDeclaration.h"
    };

#pragma region Polygon
    template <uint8 N> 
    void FShokoRayLibPlatformRenderer::DrawPath(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness) {
        for (int i = 0; i < N - 1; i++) {
            DrawLineEx(TO_RL_V2(Points[i]), TO_RL_V2(Points[i+1]), (float)BorderThickness, TO_RL_COLOR(Color));
        }
    }  
#pragma endregion
    
#pragma region Path
    template <uint8 N>
    void FShokoRayLibPlatformRenderer::DrawPolygonBorder(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {
        for (int i = 0; i < N; i++) {
            Vector2 p1 = TO_RL_V2(Points[i]);
            Vector2 p2 = TO_RL_V2(Points[(i + 1) % N]); // Замыкаем полигон
            DrawLineEx(p1, p2, (float)BorderThickness, TO_RL_COLOR(Color));
        }
    }
#pragma endregion

    using FShokoPlatformRenderer = FShokoRayLibPlatformRenderer;
}
