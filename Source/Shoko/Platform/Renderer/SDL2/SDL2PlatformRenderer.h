#pragma once

#include <SDL.h>

#include "Core/Aliases.h"
#include "Core/Math.h"
#include "Types/Color.h"
#include "Types/Renderer.h"
#include "Types/StaticArray.h"
#include "Types/Vector2D.h"

namespace Shoko
{
    struct FAngle;
    
    class FShokoSDL2PlatformRenderer
    {
#include "../RendererDeclaration.h"
        
    public:
        static SDL_Renderer* SDLRenderer;
    };

#pragma region Polygon
        template <uint8 N>
        void FShokoSDL2PlatformRenderer::DrawPolygonBorder(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
        {
            if (!SDLRenderer || BorderThickness == 0 || N < 2) return;

            SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

            for (uint8 i = 0; i < N; ++i) {
                FLocation P1 = Points[i];
                FLocation P2 = Points[(i + 1) % N];

                // Вычисляем вектор направления ребра
                float dx = P2.X - P1.X;
                float dy = P2.Y - P1.Y;
                float Length = FMath::Sqrt(dx * dx + dy * dy);
                if (Length < 0.001f) continue;

                // Нормализованный вектор перпендикуляра (нормаль)
                // Для 2D это (-dy, dx) — обычно смотрит "наружу" при CCW обходе
                float NX = -dy / Length;
                float NY = dx / Length;

                // Определяем смещение в зависимости от BorderType
                float OffsetStart, OffsetEnd;
                float T = (float)BorderThickness;

                switch (BorderType) {
                case EShokoRendererBorderType::Inside:  OffsetStart = -T; OffsetEnd = 0; break;
                case EShokoRendererBorderType::Outside: OffsetStart = 0;  OffsetEnd = T; break;
                case EShokoRendererBorderType::Both:    OffsetStart = -T/2.0f; OffsetEnd = T/2.0f; break;
                }

                // Рисуем "толстое" ребро как набор параллельных линий вдоль нормали
                for (float t = OffsetStart; t <= OffsetEnd; t += 0.5f) {
                    SDL_RenderDrawLine(SDLRenderer, 
                        (int)(P1.X + NX * t), (int)(P1.Y + NY * t), 
                        (int)(P2.X + NX * t), (int)(P2.Y + NY * t));
                }
            }
        }
#pragma endregion
        
#pragma region Path
        template <uint8 N>
        void FShokoSDL2PlatformRenderer::DrawPath(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness)
        {
            // Путь должен содержать как минимум две точки
            if (!SDLRenderer || BorderThickness == 0 || N < 2) return;

            SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

            // Проходим по всем сегментам пути (от 0 до N-2)
            for (uint8 i = 0; i < N - 1; ++i)
            {
                FLocation P1 = Points[i];
                FLocation P2 = Points[i + 1];

                // 1. Вычисляем вектор направления сегмента
                float dx = P2.X - P1.X;
                float dy = P2.Y - P1.Y;
                float Length = FMath::Sqrt(dx * dx + dy * dy);

                // Пропускаем слишком короткие сегменты, чтобы избежать деления на ноль
                if (Length < 0.001f) continue;

                // 2. Вычисляем нормаль (перпендикуляр) к сегменту
                // Нормализованный вектор (-dy, dx)
                float NX = -dy / Length;
                float NY = dx / Length;

                // 3. Рисуем "толщину" сегмента
                // Распределяем толщину в обе стороны от линии (как Both)
                float HalfT = (float)BorderThickness / 2.0f;

                for (float t = -HalfT; t <= HalfT; t += 0.5f)
                {
                    SDL_RenderDrawLine(SDLRenderer, 
                        (int)(P1.X + NX * t), (int)(P1.Y + NY * t), 
                        (int)(P2.X + NX * t), (int)(P2.Y + NY * t)
                    );
                }

                // 4. Опционально: Сглаживание стыков (Joints)
                // При больших значениях толщины на углах могут быть пустые треугольники.
                // Чтобы их закрыть, рисуем заполненный круг в каждой точке сочленения.
                if (BorderThickness > 2)
                {
                    // Можно вызвать реализованный ранее DrawCircle с радиусом HalfT
                    // в точках P1 и P2, чтобы стыки были идеально круглыми.
                }
            }
        }
#pragma endregion

    using FShokoPlatformRenderer = FShokoSDL2PlatformRenderer;
}
