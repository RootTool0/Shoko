#include <vector>

#include "Config.h"
#include "Core/Math.h"
#if SHOKO_RENDERER == SHOKO_RENDERER_HDMI
#include "HDMIPlatformRenderer.h"

#include <fstream>
#include <cstdint>
#include <iostream>

using namespace Shoko;

std::ofstream FShokoHDMIPlatformRenderer::FrameBuffer;
static std::vector<uint32> BackBuffer; 

bool FShokoHDMIPlatformRenderer::Initialize()
{
    FrameBuffer.open("/dev/fb0", std::ios::binary);
    
    if(!FrameBuffer)
    {
        std::cerr << "Cannot open /dev/fb1\n";
        return false;
    }
    
    BackBuffer.assign(ScreenWidth * ScreenHeight, 0);
    
    return true;
}

void FShokoHDMIPlatformRenderer::Deinitialize()
{
    if(FrameBuffer.is_open())
        FrameBuffer.close();
    
    BackBuffer.clear();
}

void FShokoHDMIPlatformRenderer::PreRender()
{
    
}

void FShokoHDMIPlatformRenderer::PostRender()
{
    if(!FrameBuffer.is_open()) return;
    
    FrameBuffer.seekp(0, std::ios::beg);
    FrameBuffer.write(reinterpret_cast<char*>(BackBuffer.data()), BackBuffer.size() * 4);
    FrameBuffer.flush();
}

void FShokoHDMIPlatformRenderer::Fill(FColor Color)
{
    std::fill(BackBuffer.begin(), BackBuffer.end(), Color.ToARGB());
}

void FShokoHDMIPlatformRenderer::DrawRect(FGeometry Geometry, FColor Color)
{
    uint32_t RawColor = Color.ToARGB();
    
    uint16_t RGB565 = Color.ToRGB565();
    uint16 x0 = FMath::Max<uint16>(0, Geometry.Location.X);
    uint16 y0 = FMath::Max<uint16>(0, Geometry.Location.Y);
    uint16 x1 = FMath::Min<uint16>(ScreenWidth,  Geometry.Location.X + Geometry.Size.X);
    uint16 y1 = FMath::Min<uint16>(ScreenHeight, Geometry.Location.Y + Geometry.Size.Y);
    
    for(int32_t y = y0; y < y1; ++y)
    {
        uint32_t row_offset = y * ScreenWidth;
        for(int32_t x = x0; x < x1; ++x)
        {
            BackBuffer[row_offset + x] = RawColor;
        }
    }
}

#endif
