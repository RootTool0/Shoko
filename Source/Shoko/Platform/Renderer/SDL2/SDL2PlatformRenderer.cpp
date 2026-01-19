#include "Config.h"
#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2

#include "SDL2PlatformRenderer.h"
#include "Types/Renderer.h"
#include "Types/Angle.h"

#include <iostream>

using namespace Shoko;

SDL_Renderer* FShokoSDL2PlatformRenderer::SDLRenderer = nullptr;

#pragma region Init
bool FShokoSDL2PlatformRenderer::Initialize() { return true; }
void FShokoSDL2PlatformRenderer::Deinitialize() {}
void FShokoSDL2PlatformRenderer::PreRender() {}

void FShokoSDL2PlatformRenderer::PostRender()
{
    if(!SDLRenderer) return;
    
    SDL_RenderPresent(SDLRenderer);
}
#pragma endregion

#pragma region Base
void FShokoSDL2PlatformRenderer::Fill(FColor Color)
{
    if(!SDLRenderer) return;
    
    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderClear(SDLRenderer);
}

void FShokoSDL2PlatformRenderer::DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness)
{
    if(!SDLRenderer || Thickness == 0) return;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    if (Thickness == 1) {
        SDL_RenderDrawLine(SDLRenderer, Start.X, Start.Y, End.X, End.Y);
    } else {
        // Рисуем несколько линий со смещением для имитации толщины
        int Offset = Thickness / 2;
        for (int i = -Offset; i < Thickness - Offset; ++i) {
            // Смещаем по нормали или просто по X/Y (для простоты здесь по Y)
            SDL_RenderDrawLine(SDLRenderer, Start.X, Start.Y + i, End.X, End.Y + i);
        }
    }
}

void FShokoSDL2PlatformRenderer::DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if (!SDLRenderer || BorderThickness == 0) return;

    // 1. Расчет радиусов (решаем проблему "Both" здесь)
    float MinR, MaxR;
    float HalfThickness = BorderThickness / 2.0f;

    switch (BorderType)
    {
    case EShokoRendererBorderType::Inside:
        MinR = (float)Radius - BorderThickness;
        MaxR = (float)Radius;
        break;
    case EShokoRendererBorderType::Outside:
        MinR = (float)Radius;
        MaxR = (float)Radius + BorderThickness;
        break;
    case EShokoRendererBorderType::Both:
        MinR = (float)Radius - HalfThickness;
        MaxR = (float)Radius + HalfThickness;
        break;
    }

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    float StartRad = StartAngle.GetRadians();
    float EndRad = EndAngle.GetRadians();
    float AngleDiff = EndRad - StartRad;

    // Адаптивное кол-во сегментов: чем больше радиус, тем больше линий
    int Segments = std::max(10, static_cast<int>(std::abs(AngleDiff) * MaxR / 1.5f));

    for (int i = 0; i < Segments; ++i)
    {
        float Alpha1 = StartRad + (AngleDiff * i / Segments);
        float Alpha2 = StartRad + (AngleDiff * (i + 1) / Segments);

        float C1 = cosf(Alpha1), S1 = sinf(Alpha1);
        float C2 = cosf(Alpha2), S2 = sinf(Alpha2);

        // Рисуем "кусочную линию" для каждого слоя толщины
        // Шаг 0.5f гарантирует отсутствие дырок между пикселями
        for (float r = MinR; r <= MaxR; r += 0.5f)
        {
            SDL_RenderDrawLine(SDLRenderer, 
                Center.X + (int)(r * C1), Center.Y + (int)(r * S1),
                Center.X + (int)(r * C2), Center.Y + (int)(r * S2)
            );
        }
    }
}
#pragma endregion

#pragma region Rect
void FShokoSDL2PlatformRenderer::DrawRect(FLocation TopLeft, FSize Size, FColor Color)
{
    if(!SDLRenderer) return;

    const SDL_Rect Rect = { TopLeft.X, TopLeft.Y, Size.X, Size.Y };
    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderFillRect(SDLRenderer, &Rect);
}

void FShokoSDL2PlatformRenderer::DrawRectBorder(FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if(!SDLRenderer || BorderThickness == 0) return;

    if(BorderType == EShokoRendererBorderType::Outside)
    {
        TopLeft -= BorderThickness;
        Size    += BorderThickness << 1;
    }
    else if(BorderType == EShokoRendererBorderType::Both)
    {
        TopLeft -= BorderThickness >> 1;
        Size    += BorderThickness;
    }
    
    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);
    
    const SDL_Rect Top =    { TopLeft.X,                            TopLeft.Y,                            Size.X,          BorderThickness };
    const SDL_Rect Bottom = { TopLeft.X,                            TopLeft.Y + Size.Y - BorderThickness, Size.X,          BorderThickness };
    const SDL_Rect Left =   { TopLeft.X,                            TopLeft.Y + BorderThickness,          BorderThickness, Size.Y - BorderThickness * 2 };
    const SDL_Rect Right =  { TopLeft.X + Size.X - BorderThickness, TopLeft.Y + BorderThickness,          BorderThickness, Size.Y - BorderThickness * 2 };
    
    SDL_RenderFillRect(SDLRenderer, &Top);
    SDL_RenderFillRect(SDLRenderer, &Bottom);
    SDL_RenderFillRect(SDLRenderer, &Left);
    SDL_RenderFillRect(SDLRenderer, &Right);
}
#pragma endregion

#pragma region Rounded Rect
void FShokoSDL2PlatformRenderer::DrawRoundedRect(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color)
{
    if (!SDLRenderer) return;
    
    // Ограничиваем радиус, чтобы он не превышал половины стороны
    uint8 R = std::min({CornerRadius, (uint8)(Size.X / 2), (uint8)(Size.Y / 2)});
    float X = TopLeft.X, Y = TopLeft.Y, W = Size.X, H = Size.Y;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    // 1. Рисуем основной "крест" (тело прямоугольника)
    SDL_Rect Center = { (int)(X + R), (int)Y, (int)(W - 2 * R), (int)H };
    SDL_Rect Left   = { (int)X, (int)(Y + R), (int)R, (int)(H - 2 * R) };
    SDL_Rect Right  = { (int)(X + W - R), (int)(Y + R), (int)R, (int)(H - 2 * R) };
    
    SDL_RenderFillRect(SDLRenderer, &Center);
    SDL_RenderFillRect(SDLRenderer, &Left);
    SDL_RenderFillRect(SDLRenderer, &Right);

    // 2. Рисуем 4 заполненных угла (четверть-круги)
    auto FillQuarterCircle = [&](int cx, int cy, float startAngle) {
        for (int i = 0; i <= R; ++i) { // Проход по радиусу для заполнения
            for (int a = 0; a <= 90; a += 2) { // Проход по углу
                float rad = (startAngle + a) * (M_PI / 180.0f);
                int px = cx + (int)(i * cosf(rad));
                int py = cy + (int)(i * sinf(rad));
                SDL_RenderDrawPoint(SDLRenderer, px, py);
            }
        }
    };

    FillQuarterCircle(X + R,     Y + R,     180); // Top-Left
    FillQuarterCircle(X + W - R, Y + R,     270); // Top-Right
    FillQuarterCircle(X + W - R, Y + H - R, 0);   // Bottom-Right
    FillQuarterCircle(X + R,     Y + H - R, 90);  // Bottom-Left
}

void FShokoSDL2PlatformRenderer::DrawRoundedRectBorder(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if (!SDLRenderer || BorderThickness == 0) return;

    float X = TopLeft.X, Y = TopLeft.Y, W = Size.X, H = Size.Y;
    float R = CornerRadius;
    float T = BorderThickness;

    // Определяем смещение радиуса и координат в зависимости от BorderType
    float MinR, MaxR, Offset;
    if (BorderType == EShokoRendererBorderType::Inside) {
        MinR = R - T; MaxR = R; Offset = 0;
    } else if (BorderType == EShokoRendererBorderType::Outside) {
        MinR = R; MaxR = R + T; Offset = -T;
    } else { // Both
        MinR = R - T/2.0f; MaxR = R + T/2.0f; Offset = -T/2.0f;
    }

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    // 1. Вспомогательная функция для отрисовки дуги угла (четверть кольца)
    auto DrawCorner = [&](float cx, float cy, float startAngle) {
        for (float r = MinR; r <= MaxR; r += 0.5f) {
            for (int a = 0; a <= 90; a += 2) {
                float rad = (startAngle + a) * (M_PI / 180.0f);
                int x1 = cx + (int)(r * cosf(rad));
                int y1 = cy + (int)(r * sinf(rad));
                SDL_RenderDrawPoint(SDLRenderer, x1, y1);
            }
        }
    };

    // Рисуем углы
    DrawCorner(X + R,     Y + R,     180); // TL
    DrawCorner(X + W - R, Y + R,     270); // TR
    DrawCorner(X + W - R, Y + H - R, 0);   // BR
    DrawCorner(X + R,     Y + H - R, 90);  // BL

    // 2. Рисуем прямые стороны (как FillRect, чтобы была толщина)
    // Верх
    SDL_Rect SideT = { (int)(X + R), (int)(Y + Offset), (int)(W - 2 * R), (int)T };
    // Низ
    SDL_Rect SideB = { (int)(X + R), (int)(Y + H - Offset - T), (int)(W - 2 * R), (int)T };
    // Лево
    SDL_Rect SideL = { (int)(X + Offset), (int)(Y + R), (int)T, (int)(H - 2 * R) };
    // Право
    SDL_Rect SideR = { (int)(X + W - Offset - T), (int)(Y + R), (int)T, (int)(H - 2 * R) };

    SDL_RenderFillRect(SDLRenderer, &SideT);
    SDL_RenderFillRect(SDLRenderer, &SideB);
    SDL_RenderFillRect(SDLRenderer, &SideL);
    SDL_RenderFillRect(SDLRenderer, &SideR);
}
#pragma endregion

#pragma region Circle
void FShokoSDL2PlatformRenderer::DrawCircle(FLocation Center, uint8 Radius, FColor Color)
{
    if (!SDLRenderer) return;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    for (int dy = -Radius; dy <= Radius; dy++)
    {
        // Находим горизонтальное смещение x для текущего dy по формуле x = sqrt(R^2 - dy^2)
        int dx = static_cast<int>(std::sqrt(Radius * Radius - dy * dy));
        
        // Рисуем горизонтальную полосу от -dx до +dx
        SDL_RenderDrawLine(SDLRenderer, 
            (int)Center.X - dx, (int)Center.Y + dy, 
            (int)Center.X + dx, (int)Center.Y + dy);
    }
}
void FShokoSDL2PlatformRenderer::DrawCircleBorder(FLocation Center, uint8 Radius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if (!SDLRenderer || BorderThickness == 0) return;

    float MinR, MaxR;
    float T = (float)BorderThickness;
    float R = (float)Radius;

    // 1. Вычисляем радиусы границ
    if (BorderType == EShokoRendererBorderType::Inside) {
        MinR = std::max(0.0f, R - T);
        MaxR = R;
    } else if (BorderType == EShokoRendererBorderType::Outside) {
        MinR = R;
        MaxR = R + T;
    } else { // Both
        MinR = std::max(0.0f, R - T / 2.0f);
        MaxR = R + T / 2.0f;
    }

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    // 2. Сканируем область от -MaxR до +MaxR
    for (int dy = -(int)MaxR; dy <= (int)MaxR; dy++)
    {
        // X-координата для внешнего круга
        int dxOuter = static_cast<int>(std::sqrt(MaxR * MaxR - dy * dy));
        
        // X-координата для внутреннего круга (дырки)
        int dxInner = 0;
        if (std::abs(dy) < MinR) {
            dxInner = static_cast<int>(std::sqrt(MinR * MinR - dy * dy));
        }

        // Рисуем левый сегмент границы
        SDL_RenderDrawLine(SDLRenderer, 
            (int)Center.X - dxOuter, (int)Center.Y + dy, 
            (int)Center.X - dxInner, (int)Center.Y + dy);
            
        // Рисуем правый сегмент границы
        SDL_RenderDrawLine(SDLRenderer, 
            (int)Center.X + dxInner, (int)Center.Y + dy, 
            (int)Center.X + dxOuter, (int)Center.Y + dy);
    }
}
#pragma endregion

#pragma region Ellipse
void FShokoSDL2PlatformRenderer::DrawEllipse(FLocation Center, FSize Size, FColor Color)
{
    if (!SDLRenderer || Size.X <= 0 || Size.Y <= 0) return;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    for (int dy = -(int)Size.Y; dy <= (int)Size.Y; dy++)
    {
        // Нормализованная высота (от -1.0 до 1.0)
        float normalizedY = (float)dy / Size.Y;
        // Вычисляем смещение X для текущей строки
        int dx = static_cast<int>(Size.X * std::sqrt(1.0f - normalizedY * normalizedY));

        SDL_RenderDrawLine(SDLRenderer, 
            (int)Center.X - dx, (int)Center.Y + dy, 
            (int)Center.X + dx, (int)Center.Y + dy);
    }
}
void FShokoSDL2PlatformRenderer::DrawEllipseBorder(FLocation Center, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if (!SDLRenderer || BorderThickness == 0 || Size.X <= 0 || Size.Y <= 0) return;

    float T = (float)BorderThickness;
    float MinRx, MaxRx, MinRy, MaxRy;

    // 1. Расчет внутреннего и внешнего радиусов для X и Y осей
    switch (BorderType)
    {
        case EShokoRendererBorderType::Inside:
            MinRx = std::max(0.0f, Size.X - T); MaxRx = Size.X;
            MinRy = std::max(0.0f, Size.Y - T); MaxRy = Size.Y;
            break;
        case EShokoRendererBorderType::Outside:
            MinRx = Size.X; MaxRx = Size.X + T;
            MinRy = Size.Y; MaxRy = Size.Y + T;
            break;
        case EShokoRendererBorderType::Both:
            float half = T / 2.0f;
            MinRx = std::max(0.0f, Size.X - half); MaxRx = Size.X + half;
            MinRy = std::max(0.0f, Size.Y - half); MaxRy = Size.Y + half;
            break;
    }

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    // 2. Сканирование по вертикали самого большого (внешнего) эллипса
    for (int dy = -(int)MaxRy; dy <= (int)MaxRy; dy++)
    {
        // X для внешнего края
        float normYOuter = (float)dy / MaxRy;
        int dxOuter = static_cast<int>(MaxRx * std::sqrt(1.0f - normYOuter * normYOuter));

        // X для внутреннего края (дырка)
        int dxInner = 0;
        if (std::abs(dy) < MinRy)
        {
            float normYInner = (float)dy / MinRy;
            dxInner = static_cast<int>(MinRx * std::sqrt(1.0f - normYInner * normYInner));
        }

        // Рисуем левую и правую части границы
        SDL_RenderDrawLine(SDLRenderer, (int)Center.X - dxOuter, (int)Center.Y + dy, (int)Center.X - dxInner, (int)Center.Y + dy);
        SDL_RenderDrawLine(SDLRenderer, (int)Center.X + dxInner, (int)Center.Y + dy, (int)Center.X + dxOuter, (int)Center.Y + dy);
    }
}
#pragma endregion

#pragma region Circle Sector
void FShokoSDL2PlatformRenderer::DrawCircleSector(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color)
{
    if (!SDLRenderer || Radius == 0) return;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    float StartRad = StartAngle.GetRadians();
    float EndRad = EndAngle.GetRadians();
    
    // Если End < Start, значит сектор проходит через 0 (360)
    float AngleDiff = EndRad - StartRad;
    if (AngleDiff < 0) AngleDiff += M_PI * 2.0f;

    // Количество шагов зависит от длины дуги для плавности
    int Segments = std::max(30, static_cast<int>(Radius * AngleDiff * 2.0f));

    for (int i = 0; i <= Segments; ++i)
    {
        float CurrentAngle = StartRad + (AngleDiff * i / Segments);
        int EndX = Center.X + static_cast<int>(Radius * cosf(CurrentAngle));
        int EndY = Center.Y + static_cast<int>(Radius * sinf(CurrentAngle));
        
        SDL_RenderDrawLine(SDLRenderer, (int)Center.X, (int)Center.Y, EndX, EndY);
    }
}
void FShokoSDL2PlatformRenderer::DrawCircleSectorBorder(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if (!SDLRenderer || BorderThickness == 0) return;

    float T = (float)BorderThickness;
    float R = (float)Radius;
    float MinR, MaxR;

    // 1. Определяем диапазон радиусов (как в DrawCircle)
    if (BorderType == EShokoRendererBorderType::Inside) {
        MinR = std::max(0.0f, R - T); MaxR = R;
    } else if (BorderType == EShokoRendererBorderType::Outside) {
        MinR = R; MaxR = R + T;
    } else { // Both
        MinR = std::max(0.0f, R - T / 2.0f); MaxR = R + T / 2.0f;
    }

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    float StartRad = StartAngle.GetRadians();
    float EndRad = EndAngle.GetRadians();
    float AngleDiff = EndRad - StartRad;
    if (AngleDiff < 0) AngleDiff += M_PI * 2.0f;

    // 2. Рисуем ДУГУ (Arc)
    int ArcSegments = std::max(20, static_cast<int>(MaxR * AngleDiff));
    for (int i = 0; i < ArcSegments; ++i)
    {
        float A1 = StartRad + (AngleDiff * i / ArcSegments);
        float A2 = StartRad + (AngleDiff * (i + 1) / ArcSegments);
        
        float Cos1 = cosf(A1), Sin1 = sinf(A1);
        float Cos2 = cosf(A2), Sin2 = sinf(A2);

        // Заполняем толщину дуги
        for (float r = MinR; r <= MaxR; r += 0.5f) {
            SDL_RenderDrawLine(SDLRenderer, 
                Center.X + (int)(r * Cos1), Center.Y + (int)(r * Sin1),
                Center.X + (int)(r * Cos2), Center.Y + (int)(r * Sin2));
        }
    }

    // 3. Рисуем ДВЕ РАДИАЛЬНЫЕ ЛИНИИ
    auto DrawThickRadialLine = [&](float angle) {
        float Cos = cosf(angle);
        float Sin = sinf(angle);
        
        // Линия должна идти от центра до MaxR (или MinR до MaxR)
        // Чтобы линия имела толщину "в бок", а не в длину, 
        // мы рисуем несколько линий с небольшим угловым смещением
        float AngularWidth = T / MaxR; // Приблизительное угловое приращение для толщины
        
        float AngleStartOffset;
        if (BorderType == EShokoRendererBorderType::Inside) AngleStartOffset = 0; 
        else if (BorderType == EShokoRendererBorderType::Outside) AngleStartOffset = -AngularWidth;
        else AngleStartOffset = -AngularWidth / 2.0f;

        for (float a = 0; a <= AngularWidth; a += 0.01f) {
            float CurrentA = angle + AngleStartOffset + a;
            int X2 = Center.X + (int)(MaxR * cosf(CurrentA));
            int Y2 = Center.Y + (int)(MaxR * sinf(CurrentA));
            SDL_RenderDrawLine(SDLRenderer, (int)Center.X, (int)Center.Y, X2, Y2);
        }
    };

    DrawThickRadialLine(StartRad);
    DrawThickRadialLine(EndRad);
}
#pragma endregion

#pragma region Bezier
void FShokoSDL2PlatformRenderer::DrawQuadraticBezier(FLocation A, FLocation B, FLocation C, FColor Color)
{
    if (!SDLRenderer) return;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    const int Segments = 50; // Количество отрезков для аппроксимации
    FLocation PreviousPoint = A;

    for (int i = 1; i <= Segments; ++i)
    {
        float t = (float)i / Segments;
        float invT = 1.0f - t;

        // Вычисление точки по формуле квадратичного Безье
        float X = invT * invT * A.X + 2.0f * invT * t * B.X + t * t * C.X;
        float Y = invT * invT * A.Y + 2.0f * invT * t * B.Y + t * t * C.Y;

        SDL_RenderDrawLine(SDLRenderer, (int)PreviousPoint.X, (int)PreviousPoint.Y, (int)X, (int)Y);
        
        PreviousPoint.X = X;
        PreviousPoint.Y = Y;
    }
}
void FShokoSDL2PlatformRenderer::DrawCubicBezier(FLocation A, FLocation B, FLocation C, FLocation D, FColor Color)
{
    if (!SDLRenderer) return;

    SDL_SetRenderDrawColor(SDLRenderer, Color.R, Color.G, Color.B, Color.A);

    const int Segments = 100; // Для кубической нужно больше сегментов для плавности
    FLocation PreviousPoint = A;

    for (int i = 1; i <= Segments; ++i)
    {
        float t = (float)i / Segments;
        float invT = 1.0f - t;
        float t2 = t * t;
        float invT2 = invT * invT;

        // Вычисление точки по формуле кубического Безье
        float X = invT2 * invT * A.X + 
                  3.0f * invT2 * t * B.X + 
                  3.0f * invT * t2 * C.X + 
                  t2 * t * D.X;

        float Y = invT2 * invT * A.Y + 
                  3.0f * invT2 * t * B.Y + 
                  3.0f * invT * t2 * C.Y + 
                  t2 * t * D.Y;

        SDL_RenderDrawLine(SDLRenderer, (int)PreviousPoint.X, (int)PreviousPoint.Y, (int)X, (int)Y);
        
        PreviousPoint.X = X;
        PreviousPoint.Y = Y;
    }
}
#pragma endregion

#endif
