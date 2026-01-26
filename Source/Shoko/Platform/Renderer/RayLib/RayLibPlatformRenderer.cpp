#include "RayLibPlatformRenderer.h"
#include "Types/Renderer.h"
#include "Types/Angle.h"

using namespace Shoko;

void CalculateBorderRadii(float Radius, float Thickness, EShokoRendererBorderType Type, float& OutInner, float& OutOuter)
{
    switch (Type) {
    case EShokoRendererBorderType::Inside:
        OutInner = Radius - Thickness;
        OutOuter = Radius;
        break;
    case EShokoRendererBorderType::Outside:
        OutInner = Radius;
        OutOuter = Radius + Thickness;
        break;
    case EShokoRendererBorderType::Both:
        OutInner = Radius - Thickness * 0.5f;
        OutOuter = Radius + Thickness * 0.5f;
        break;
    }
}

void ApplyBorderToRect(Rectangle& Rect, float Thickness, EShokoRendererBorderType Type)
{
    if (Type == EShokoRendererBorderType::Outside) {
        Rect.x -= Thickness; Rect.y -= Thickness;
        Rect.width += Thickness * 2; Rect.height += Thickness * 2;
    } else if (Type == EShokoRendererBorderType::Both) {
        float half = Thickness * 0.5f;
        Rect.x -= half; Rect.y -= half;
        Rect.width += Thickness; Rect.height += Thickness;
    }
}

#pragma region Init
bool FShokoRayLibPlatformRenderer::Initialize() { SetTraceLogLevel(LOG_NONE); return IsWindowReady(); }
void FShokoRayLibPlatformRenderer::Deinitialize() {}
void FShokoRayLibPlatformRenderer::PreRender() { BeginDrawing(); }
void FShokoRayLibPlatformRenderer::PostRender() { EndDrawing(); }
#pragma endregion

#pragma region Base
void FShokoRayLibPlatformRenderer::Fill(FColor Color) { ClearBackground(TO_RL_COLOR(Color)); }
void FShokoRayLibPlatformRenderer::DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness) {
    DrawLineEx(TO_RL_V2(Start), TO_RL_V2(End), (float)Thickness, TO_RL_COLOR(Color));
}
void FShokoRayLibPlatformRenderer::DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {
    float inner, outer;
    CalculateBorderRadii((float)Radius, (float)BorderThickness, BorderType, inner, outer);
        
    // В Raylib DrawRing рисует "кольцо" или его часть. Идеально для Arc с толщиной.
    DrawRing(TO_RL_V2(Center), inner, outer, StartAngle.GetDegrees(), EndAngle.GetDegrees(), 36, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Rect
void FShokoRayLibPlatformRenderer::DrawRect(FLocation TopLeft, FSize Size, FColor Color) { DrawRectangle((int)TopLeft.X, (int)TopLeft.Y, (int)Size.X, (int)Size.Y, TO_RL_COLOR(Color)); }

void FShokoRayLibPlatformRenderer::DrawRectBorder(FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    Rectangle rect = { (float)TopLeft.X, (float)TopLeft.Y, (float)Size.X, (float)Size.Y };
    ApplyBorderToRect(rect, (float)BorderThickness, BorderType);
    DrawRectangleLinesEx(rect, (float)BorderThickness, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Rounded Rect
void FShokoRayLibPlatformRenderer::DrawRoundedRect(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color)
{
    Rectangle rect = { static_cast<float>(TopLeft.X), static_cast<float>(TopLeft.Y), static_cast<float>(Size.X), static_cast<float>(Size.Y) };
    float roundness = static_cast<float>(CornerRadius) / (static_cast<float>(Size.Y) / 2.f); 
    DrawRectangleRounded(rect, roundness, 16, TO_RL_COLOR(Color));
}

void FShokoRayLibPlatformRenderer::DrawRoundedRectBorder(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    Rectangle rect = { static_cast<float>(TopLeft.X), static_cast<float>(TopLeft.Y), static_cast<float>(Size.X), static_cast<float>(Size.Y) };
    ApplyBorderToRect(rect, BorderThickness, BorderType);
    float roundness = (rect.height > 0) ? static_cast<float>(CornerRadius) / (rect.height * 0.5f) : 0.0f;
    DrawRectangleRoundedLines(rect, roundness, 16, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Circle
void FShokoRayLibPlatformRenderer::DrawCircle(FLocation Center, uint8 Radius, FColor Color)
{
    DrawCircleV(TO_RL_V2(Center), (float)Radius, TO_RL_COLOR(Color));
}
void FShokoRayLibPlatformRenderer::DrawCircleBorder(FLocation Center, uint8 Radius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    float inner, outer;
    CalculateBorderRadii((float)Radius, (float)BorderThickness, BorderType, inner, outer);
    DrawRing(TO_RL_V2(Center), inner, outer, 0.0f, 360.0f, 36, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Ellipse
void FShokoRayLibPlatformRenderer::DrawEllipse(FLocation Center, FSize Size, FColor Color)
{
    ::DrawEllipse(Center.X, Center.Y, static_cast<float>(Size.X) / 2.f, static_cast<float>(Size.Y) / 2.f, TO_RL_COLOR(Color));
}
void FShokoRayLibPlatformRenderer::DrawEllipseBorder(FLocation Center, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    DrawEllipseLines(Center.X, Center.Y, static_cast<float>(Size.X) / 2.f, static_cast<float>(Size.Y) / 2.f, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Circle Sector
void FShokoRayLibPlatformRenderer::DrawCircleSector(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color) {
    ::DrawCircleSector(TO_RL_V2(Center), (float)Radius, StartAngle.GetDegrees(), EndAngle.GetDegrees(), 36, TO_RL_COLOR(Color));
}

void FShokoRayLibPlatformRenderer::DrawCircleSectorBorder(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {
    float inner, outer;
    CalculateBorderRadii((float)Radius, (float)BorderThickness, BorderType, inner, outer);
    DrawRing(TO_RL_V2(Center), inner, outer, StartAngle.GetDegrees(), EndAngle.GetDegrees(), 36, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Bezier
void FShokoRayLibPlatformRenderer::DrawQuadraticBezier(FLocation A, FLocation B, FLocation C, FColor Color)
{
    DrawSplineSegmentBezierQuadratic(TO_RL_V2(A), TO_RL_V2(B), TO_RL_V2(C), 2.0f, TO_RL_COLOR(Color));
}
void FShokoRayLibPlatformRenderer::DrawCubicBezier(FLocation A, FLocation B, FLocation C, FLocation D, FColor Color)
{
    DrawSplineSegmentBezierCubic(TO_RL_V2(A), TO_RL_V2(B), TO_RL_V2(C), TO_RL_V2(D), 2.0f, TO_RL_COLOR(Color));
}
#pragma endregion

#pragma region Text
void FShokoRayLibPlatformRenderer::DrawText(FLocation Center, const char* Text, uint16 Len, uint8 Size, FColor Color, bool bCentered)
{
    if(!Text || Len == 0) return;

    const char* FormattedText = TextFormat("%.*s", Len, Text);
    int PosX = static_cast<int>(Center.X);
    int PosY = static_cast<int>(Center.Y);

    if (bCentered)
    {
        Vector2 MeasuredSize = MeasureTextEx(GetFontDefault(), FormattedText, (float)Size, 1.0f);
        PosX -= static_cast<int>(MeasuredSize.x / 2.0f);
        PosY -= static_cast<int>(MeasuredSize.y / 2.0f);
    }
    
    ::DrawText(FormattedText, PosX, PosY, Size, TO_RL_COLOR(Color));
}
#pragma endregion
