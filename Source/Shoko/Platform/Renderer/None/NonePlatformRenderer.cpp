#include "NonePlatformRenderer.h"

#include "Types/Color.h"
#include "Types/Vector2D.h"
#include "Types/Renderer.h"
#include "Types/Angle.h"

using namespace Shoko;

bool FShokoNonePlatformRenderer::Initialize() { return true; }
void FShokoNonePlatformRenderer::Deinitialize() {}
void FShokoNonePlatformRenderer::PreRender() {}
void FShokoNonePlatformRenderer::PostRender() {}

void FShokoNonePlatformRenderer::Fill(FColor Color) {}
void FShokoNonePlatformRenderer::DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness) {}
void FShokoNonePlatformRenderer::DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}

void FShokoNonePlatformRenderer::DrawRect(FLocation TopLeft, FSize Size, FColor Color) {}
void FShokoNonePlatformRenderer::DrawRectBorder(FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}

void FShokoNonePlatformRenderer::DrawRoundedRect(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color) {}
void FShokoNonePlatformRenderer::DrawRoundedRectBorder(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}

void FShokoNonePlatformRenderer::DrawCircle(FLocation Center, uint8 Radius, FColor Color) {}
void FShokoNonePlatformRenderer::DrawCircleBorder(FLocation Center, uint8 Radius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}

void FShokoNonePlatformRenderer::DrawEllipse(FLocation Center, FSize Size, FColor Color) {}
void FShokoNonePlatformRenderer::DrawEllipseBorder(FLocation Center, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}

void FShokoNonePlatformRenderer::DrawCircleSector(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color) {}
void FShokoNonePlatformRenderer::DrawCircleSectorBorder(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}

void FShokoNonePlatformRenderer::DrawQuadraticBezier(FLocation A, FLocation B, FLocation C, FColor Color) {}
void FShokoNonePlatformRenderer::DrawCubicBezier(FLocation A, FLocation B, FLocation C, FLocation D, FColor Color) {}
