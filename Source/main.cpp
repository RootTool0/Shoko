#include "Shoko/Shoko.h"
#include "Demo.h"
#include "Experimental.h"

#include <chrono>

using namespace Shoko;

bool bPage = false;
void TestOnHover2()   { bPage = true; }
void TestOnUnhover2() { bPage = false; }

constexpr auto RootWidget = 
    SNew<SButton>()
        .SetPosition(500, 0)
        .SetSize(500, 700)
        .OnHover(&TestOnHover2)
        .OnUnhover(&TestOnUnhover2)
        .SetColor(FColor(255, 50, 50, 0));

int main()
{
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    auto Window = SWindow()
        .SetSize(FUIntVector2D(1000, 700))
        .SetTitle("Shoko - Compile-time UI Framework [Rendering Tech Demo]");
    Window.ActivateRenderContext();
    
    auto LastTime = std::chrono::high_resolution_clock::now();
    float MaxFPS = 0;
    while(true)
    {
        if(FShokoInput::PullEvents().Key == EKey::Window_Close) break;
        
        Experimental::TestMouseSystem(RootWidget.HitTest(FShokoInput::GetMousePosition()));
        bPage ? Demo::AllPrimitives() : Demo::TestUI();
        
        {
            auto EndTime = std::chrono::high_resolution_clock::now();
            float FPS = 1.0f / std::chrono::duration<float>(EndTime - LastTime).count();
            if(FPS > MaxFPS) MaxFPS = FPS;
            printf("FPS: %.2f (Max: %.2f)\r", FPS, MaxFPS);
            fflush(stdout);
            LastTime = EndTime;
        }
    }
    
    Window.Deinitialize();
    FShokoInput::Deinitialize();
    FShokoRenderer::Deinitialize();
    
    return 0;
}
