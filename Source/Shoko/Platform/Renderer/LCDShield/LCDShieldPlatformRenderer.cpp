#include <vector>

#include "../../../Config.h"
#if SHOKO_RENDERER == SHOKO_RENDERER_LCDShield
#include "LCDShieldPlatformRenderer.h"

#include <fstream>
#include <cstdint>
#include <iostream>

using namespace Shoko;

std::ofstream FShokoLCDShieldPlatformRenderer::FrameBuffer;

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

void FShokoLCDShieldPlatformRenderer::Deinitialize()
{
    if(!FrameBuffer.is_open()) return;
    
    FrameBuffer.close();
}

void FShokoLCDShieldPlatformRenderer::PreRender()
{
    if(!FrameBuffer.is_open()) return;
    
    FrameBuffer.seekp(0, std::ios::beg);
}

void FShokoLCDShieldPlatformRenderer::PostRender()
{
    if(!FrameBuffer.is_open()) return;
    
    FrameBuffer.flush();
}

void FShokoLCDShieldPlatformRenderer::Fill(FColor Color)
{
    if (!FrameBuffer.is_open()) return;

    uint16_t RGB565 = Color.ToRGB565();
    
    for(int i = 0; i < ScreenWidth * ScreenHeight; i++)
        FrameBuffer.write(reinterpret_cast<char*>(&RGB565), 2);
}

void FShokoLCDShieldPlatformRenderer::DrawRect(FGeometry Geometry, FColor Color)
{
    if(!FrameBuffer.is_open()) return;

    uint16_t RGB565 = Color.ToRGB565();
    uint16 x0 = std::max<short>(0, Geometry.Location.X);
    uint16 y0 = std::max<short>(0, Geometry.Location.Y);
    uint16 x1 = std::min<int>(ScreenWidth,  Geometry.Location.X + Geometry.Size.X);
    uint16 y1 = std::min<int>(ScreenHeight, Geometry.Location.Y + Geometry.Size.Y);

    for(uint16 y = y0; y < y1; ++y)
    {
        FrameBuffer.seekp((y * ScreenWidth + x0) * 2, std::ios::beg);
        for(uint16 x = x0; x < x1; ++x)
            FrameBuffer.write(reinterpret_cast<char*>(&RGB565), 2);
    }
} 

#endif
