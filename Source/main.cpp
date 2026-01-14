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

int main()
{
    FShokoRenderer::Initialize();
    
    auto Window = SWindow()
        .SetSize(FUIntVector2D(320, 480))
        .SetTitle("Hello From Shoko! [SDL2]");
    
    Window.ActivateRenderContext();
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (true)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                break;
        
        auto startTime = std::chrono::high_resolution_clock::now();
        
        FShokoRenderer::PreRender();
        FShokoRenderer::Fill(FColor(30, 30, 120));
        RootWidget.Render();
        FShokoRenderer::PostRender();
        
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = endTime - lastTime;
        lastTime = endTime;

        float fps = 1.0f / delta.count();
        printf("FPS: %.2f\r", fps);
        fflush(stdout);
    }
    
    Window.Deinitialize();
    
    return 0;
}
