#include "LCDShieldPlatformRenderer.h"

#include <fstream>
#include <cstdint>
#include <iostream>

#include "Types/Angle.h"
#include "Types/Renderer.h"

using namespace Shoko;

std::ofstream FShokoLCDShieldPlatformRenderer::FrameBuffer;

#pragma region Init
bool FShokoLCDShieldPlatformRenderer::Initialize()
{
    FrameBuffer.open("/dev/fb1", std::ios::binary);
    
    if(!FrameBuffer)
    {
        std::cerr << "Cannot open /dev/fb1\n";
        return false;
    }
    
    return true;
}
void FShokoLCDShieldPlatformRenderer::Deinitialize() { if(FrameBuffer.is_open()) FrameBuffer.close(); }
void FShokoLCDShieldPlatformRenderer::PreRender()    { if(FrameBuffer.is_open()) FrameBuffer.seekp(0, std::ios::beg); }
void FShokoLCDShieldPlatformRenderer::PostRender()   { if(FrameBuffer.is_open()) FrameBuffer.flush(); }
#pragma endregion

#pragma region Base
void FShokoLCDShieldPlatformRenderer::Fill(FColor Color)
{
    if (!FrameBuffer.is_open()) return;

    uint16_t RGB565 = Color.ToRGB565();
    
    for(int i = 0; i < ScreenWidth * ScreenHeight; i++)
        FrameBuffer.write(reinterpret_cast<char*>(&RGB565), 2);
}
void FShokoLCDShieldPlatformRenderer::DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness) {}
void FShokoLCDShieldPlatformRenderer::DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Rect

void FShokoLCDShieldPlatformRenderer::DrawRect(FLocation TopLeft, FSize Size, FColor Color)
{
    if(!FrameBuffer.is_open()) return;

    uint16_t RGB565 = Color.ToRGB565();
    uint16 x0 = FMath::Max<uint16>(0, TopLeft.X);
    uint16 y0 = FMath::Max<uint16>(0, TopLeft.Y);
    uint16 x1 = FMath::Min<uint16>(ScreenWidth,  TopLeft.X + Size.X);
    uint16 y1 = FMath::Min<uint16>(ScreenHeight, TopLeft.Y + Size.Y);

    for(uint16 y = y0; y < y1; ++y)
    {
        FrameBuffer.seekp((y * ScreenWidth + x0) * 2, std::ios::beg);
        for(uint16 x = x0; x < x1; ++x)
            FrameBuffer.write(reinterpret_cast<char*>(&RGB565), 2);
    }
}

void FShokoLCDShieldPlatformRenderer::DrawRectBorder(FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Rounded Rect
void FShokoLCDShieldPlatformRenderer::DrawRoundedRect(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color) {}
void FShokoLCDShieldPlatformRenderer::DrawRoundedRectBorder(FLocation TopLeft, FSize Size, uint8 CornerRadius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Circle
void FShokoLCDShieldPlatformRenderer::DrawCircle(FLocation Center, uint8 Radius, FColor Color) {}
void FShokoLCDShieldPlatformRenderer::DrawCircleBorder(FLocation Center, uint8 Radius, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Ellipse
void FShokoLCDShieldPlatformRenderer::DrawEllipse(FLocation Center, FSize Size, FColor Color) {}
void FShokoLCDShieldPlatformRenderer::DrawEllipseBorder(FLocation Center, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Circle Sector
void FShokoLCDShieldPlatformRenderer::DrawCircleSector(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color) {}
void FShokoLCDShieldPlatformRenderer::DrawCircleSectorBorder(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Bezier
void FShokoLCDShieldPlatformRenderer::DrawQuadraticBezier(FLocation A, FLocation B, FLocation C, FColor Color) {}
void FShokoLCDShieldPlatformRenderer::DrawCubicBezier(FLocation A, FLocation B, FLocation C, FLocation D, FColor Color) {}
#pragma endregion

#pragma region Text
void FShokoLCDShieldPlatformRenderer::DrawText(FLocation Center, const char* Text, uint16 Len, uint8 Size, FColor Color, bool bCentered) {}
#pragma endregion
