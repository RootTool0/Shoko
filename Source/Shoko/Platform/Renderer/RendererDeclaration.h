#pragma once

public:

// Init
static bool Initialize();
static void Deinitialize();
static void PreRender();
static void PostRender();

// Base
static void Fill(FColor Color);
static void DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness);
static void DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);

// Rect
static void DrawRect        (FLocation TopLeft, FSize Size, FColor Color);
static void DrawRectBorder  (FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);
// TODO: static void DrawRectShadow  (FLocation TopLeft, FSize Size, FColor Color, uint8 ShadowThickness);
// TODO: static void DrawRectGradient(FLocation TopLeft, FSize Size, FColor StartColor, FColor EndColor, bool bIsVertical);

// Rounded Rect
static void DrawRoundedRect        (FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color);
static void DrawRoundedRectBorder  (FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);
// TODO: static void DrawRoundedRectShadow  (FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 ShadowThickness);
// TODO: static void DrawRoundedRectGradient(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor StartColor, FColor EndColor, bool bIsVertical);

// Circle
static void DrawCircle        (FLocation Center, uint8 Radius, FColor Color);
static void DrawCircleBorder  (FLocation Center, uint8 Radius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);
// TODO: static void DrawCircleShadow  (FLocation Center, uint8 Radius, FColor Color, uint8 ShadowThickness);
// TODO: static void DrawCircleGradient(FLocation Center, uint8 Radius, FColor CenterColor, FColor EdgeColor);

// Ellipse
static void DrawEllipse        (FLocation Center, FSize Size, FColor Color);
static void DrawEllipseBorder  (FLocation Center, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);
// TODO: static void DrawEllipseShadow  (FLocation Center, uint8 Radius, FColor Color, uint8 ShadowThickness);
// TODO: static void DrawEllipseGradient(FLocation Center, uint8 Radius, FColor CenterColor, FColor EdgeColor);

// CircleSector
static void DrawCircleSector      (FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color);
static void DrawCircleSectorBorder(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);

// Bezier
static void DrawQuadraticBezier(FLocation A, FLocation B, FLocation C, FColor Color);
static void DrawCubicBezier    (FLocation A, FLocation B, FLocation C, FLocation D, FColor Color);

// Polygon
// TODO: template <uint8 N> static void DrawPolygon      (const TStaticArray<FLocation, N>& Points, FColor Color);
template <uint8 N> static void DrawPolygonBorder(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType);

// Path
template <uint8 N> static void DrawPath(const TStaticArray<FLocation, N>& Points, FColor Color, uint8 BorderThickness);

private:
