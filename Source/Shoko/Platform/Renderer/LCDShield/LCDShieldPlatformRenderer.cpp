#include "LCDShieldPlatformRenderer.h"

#include "Types/Angle.h"
#include "Types/Renderer.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace Shoko;

uint16_t* FShokoLCDShieldPlatformRenderer::BufferPtr;
int FShokoLCDShieldPlatformRenderer::FBDescriptor;

#pragma region Init
bool FShokoLCDShieldPlatformRenderer::Initialize()
{
    FBDescriptor = open("/dev/fb1", O_RDWR);
    if(FBDescriptor < 0) return false;

    // Мапим память дисплея напрямую в адресное пространство процесса
    size_t ScreenSize = ScreenWidth * ScreenHeight * 2;
    BufferPtr = (uint16_t*)mmap(NULL, ScreenSize, PROT_READ | PROT_WRITE, MAP_SHARED, FBDescriptor, 0);
    
    return BufferPtr != MAP_FAILED;
}
void FShokoLCDShieldPlatformRenderer::Deinitialize()
{
    if(BufferPtr != MAP_FAILED) munmap(BufferPtr, ScreenWidth * ScreenHeight * 2);
    if(FBDescriptor >= 0) close(FBDescriptor);
}
void FShokoLCDShieldPlatformRenderer::PreRender() {}
void FShokoLCDShieldPlatformRenderer::PostRender()
{
    if(BufferPtr != MAP_FAILED) msync(BufferPtr, ScreenWidth * ScreenHeight * 2, MS_SYNC);
}
#pragma endregion

#pragma region Base
void FShokoLCDShieldPlatformRenderer::Fill(FColor Color)
{
    if(BufferPtr == MAP_FAILED) return;

    uint16_t RGB565 = Color.ToRGB565();
    uint32_t TotalPixels = ScreenWidth * ScreenHeight;
    
    for(uint32_t i = 0; i < TotalPixels; ++i)
        BufferPtr[i] = RGB565;
}
void FShokoLCDShieldPlatformRenderer::DrawLine(FLocation Start, FLocation End, FColor Color, uint8 Thickness) {}
void FShokoLCDShieldPlatformRenderer::DrawArc(FLocation Center, uint8 Radius, FAngle StartAngle, FAngle EndAngle, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType) {}
#pragma endregion

#pragma region Rect

void FShokoLCDShieldPlatformRenderer::DrawRect(FLocation TopLeft, FSize Size, FColor Color)
{
    if (BufferPtr == MAP_FAILED) return;

    uint16_t RGB565 = Color.ToRGB565();
    
    int x0 = std::max(0, (int)TopLeft.X);
    int y0 = std::max(0, (int)TopLeft.Y);
    int x1 = std::min((int)ScreenWidth,  (int)(TopLeft.X + Size.X));
    int y1 = std::min((int)ScreenHeight, (int)(TopLeft.Y + Size.Y));

    for (int y = y0; y < y1; ++y) {
        uint16_t* Row = BufferPtr + (y * ScreenWidth);
        for (int x = x0; x < x1; ++x) {
            Row[x] = RGB565; 
        }
    }
}

void FShokoLCDShieldPlatformRenderer::DrawRectBorder(FLocation TopLeft, FSize Size, FColor Color, uint8 BorderThickness, EShokoRendererBorderType BorderType)
{
    if (BufferPtr == MAP_FAILED || BorderThickness == 0) return;

    int16 x = TopLeft.X;
    int16 y = TopLeft.Y;
    uint16 w = Size.X;
    uint16 h = Size.Y;
    uint16 t = static_cast<uint16>(BorderThickness);

    if (BorderType == EShokoRendererBorderType::Outside) 
    {
        x -= static_cast<int16>(t); 
        y -= static_cast<int16>(t);
        w += static_cast<uint16>(t << 1); 
        h += static_cast<uint16>(t << 1);
    } 
    else if (BorderType == EShokoRendererBorderType::Both) 
    {
        uint16 half = t >> 1; 
        x -= static_cast<int16>(half); 
        y -= static_cast<int16>(half);
        w += t; 
        h += t;
    }

    DrawRect(FLocation(x, y), FSize(w, t), Color);
    DrawRect(FLocation(x, static_cast<int16>(y + h - t)), FSize(w, t), Color);
    
    if (h > (t << 1)) 
    {
        uint16 SideHeight = static_cast<uint16>(h - (t << 1));
        int16 SideY = static_cast<int16>(y + t);
        
        DrawRect(FLocation(x, SideY), FSize(t, SideHeight), Color);
        DrawRect(FLocation(static_cast<int16>(x + w - t), SideY), FSize(t, SideHeight), Color);
    }
}
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
