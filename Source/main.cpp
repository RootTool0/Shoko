#include "Shoko/Shoko.h"

using namespace Shoko;

void TestOnHover1()
{
    printf("[1] Hover\n");
}

void TestOnUnhover1()
{
    printf("[1] Unhover\n");
}

void TestOnHover2()
{
    printf("[2] Hover\n");
}

void TestOnUnhover2()
{
    printf("[2] Unhover\n");
}

constexpr auto RootWidget = SNew<SWidgetContainer>
(
    SNew<SButton>()
        .SetPosition(100, 200)
        .SetSize(200, 200)
        .OnHover(&TestOnHover1)
        .OnUnhover(&TestOnUnhover1)
        .SetColor(FColor(255, 50, 50)),
            
    SNew<SButton>()
        .SetPosition(400, 200)
        .SetSize(200, 200)
        .OnHover(&TestOnHover2)
        .OnUnhover(&TestOnUnhover2)
        .SetColor(FColor(50, 50, 255)),
    
    SNew<SBoxWidget>()
        .SetPosition(100, 200)
        .SetSize(100, 100)
        .SetColor(FColor(255, 255, 255)),
    
    SNew<SBoxWidget>()
        .SetPosition(0, 0)
        .SetSize(10, 10)
        .SetColor(FColor(0, 0, 0)),

    SNew<SBoxWidget>()
        .SetPosition(320-10, 0)
        .SetSize(10, 10)
        .SetColor(FColor(255, 0, 0)),
    
    SNew<SBoxWidget>()
        .SetPosition(0, 480-10)
        .SetSize(10, 10)
        .SetColor(FColor(0, 255, 0)),
        
    SNew<SBoxWidget>()
        .SetPosition(320-10, 480-10)
        .SetSize(10, 10)
        .SetColor(FColor(255, 255, 0))
);

#include <iostream>
#include <chrono>

size_t GetRAMUsageKB()
{
    std::ifstream status("/proc/self/status");
    std::string line;
    while (std::getline(status, line))
    {
        if (line.substr(0, 6) == "VmRSS:")
        {
            size_t kb = 0;
            sscanf(line.c_str(), "VmRSS: %zu kB", &kb);
            return kb;
        }
    }
    return 0;
}

int main()
{
    FShokoRenderer::Initialize();
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        
        FShokoRenderer::PreRender();
        FShokoRenderer::Fill(FColor(30, 30, 120));
        RootWidget.Render();
        FShokoRenderer::PostRender();
        
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = endTime - lastTime;
        lastTime = endTime;

        float fps = 1.0f / delta.count();
        size_t ramKB = GetRAMUsageKB();

        printf("FPS: %.2f | RAM: %zu KB\r", fps, ramKB);
        fflush(stdout);
    }
    
    return 0;
}
