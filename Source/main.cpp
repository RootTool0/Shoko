#include "Shoko/Shoko.h"
#include "Demo.h"
#include "Experimental.h"

#include <chrono>

using namespace Shoko;

bool bPage = false;
void TestOnHover2()   { bPage = true; }
void TestOnUnhover2() { bPage = false; }

void TestCheckBox(bool bValue) { std::cout << "CheckBox: " << (bValue ? "true" : "false") << '\n'; }
void TestSlider(float Alpha) { std::cout << "Slider: " << Alpha << '\n'; }

constexpr auto RootWidget = SNew<SWidgetContainer>(
    SNew<SSlider>()
        .SetPosition(100, 100)
        .OnValueChangeFinished(&TestSlider),

    SNew<SCheckBox>()
        .SetPosition(200, 200)
        .OnValueChanged(&TestCheckBox),
        
    SNew<SButton>()
        .SetPosition(500, 0)
        .OnHover(&TestOnHover2)
        .OnUnhover(&TestOnUnhover2)
)
.SetSize(1000, 700);

int main()
{
    Experimental::hexDump(RootWidget);
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    auto Window = SWindow()
        .SetSize(FUIntVector2D(1000, 700))
        .SetTitle("Shoko - Compile-time UI Framework");
    Window.ActivateRenderContext();
    
    auto LastTime = std::chrono::high_resolution_clock::now();
    float MaxFPS = 0;
    while(true)
    {
        if(FShokoInput::PullEvents().Key == EKey::Window_Close) break;
        
        Experimental::TestMouseSystem(RootWidget.HitTest(FShokoInput::GetMousePosition()));
        
        FShokoRenderer::PreRender();
        Demo::TestUI();
        RootWidget.Render();
        FShokoRenderer::PostRender();
        
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
