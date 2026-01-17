#include "Input.h"
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

void TestOnMouseDown1()
{
    printf("[1] Mouse Down\n");
}

void TestOnMouseUp1()
{
    printf("[1] Mouse Up\n");
}

void TestOnHover2()
{
    printf("[2] Hover\n");
}

void TestOnUnhover2()
{
    printf("[2] Unhover\n");
}

void TestOnMouseDown2()
{
    printf("[2] Mouse Down\n");
}

void TestOnMouseUp2()
{
    printf("[2] Mouse Up\n");
}

auto RootWidget = SNew<SWidgetContainer>
(
    SNew<SButton>()
        .SetPosition(100, 200)
        .SetSize(200, 200)
        .OnHover(&TestOnHover1)
        .OnUnhover(&TestOnUnhover1)
        .OnMouseDown(&TestOnMouseDown1)
        .OnMouseUp(&TestOnMouseUp1)
        .SetColor(FColor(255, 50, 50)),
            
    SNew<SButton>()
        .SetPosition(400, 200)
        .SetSize(200, 200)
        .OnHover(&TestOnHover2)
        .OnUnhover(&TestOnUnhover2)
        .OnMouseDown(&TestOnMouseDown2)
        .OnMouseUp(&TestOnMouseUp2)
        .SetColor(FColor(50, 50, 255)),
    
    SNew<SBoxWidget>()
        .SetPosition(0, 100)
        .SetSize(100, 100)
        .SetColor(FColor(255, 255, 255)),
    
    SNew<SBoxWidget>()
        .SetPosition(0, 0)
        .SetSize(10, 10)
        .SetColor(FColor(0, 0, 0)),

    SNew<SBoxWidget>()
        .SetPosition(1920-10, 0)
        .SetSize(10, 10)
        .SetColor(FColor(255, 0, 0)),
    
    SNew<SBoxWidget>()
        .SetPosition(0, 1080-10)
        .SetSize(10, 10)
        .SetColor(FColor(0, 255, 0)),
        
    SNew<SBoxWidget>()
        .SetPosition(1920-10, 1080-10)
        .SetSize(10, 10)
        .SetColor(FColor(255, 255, 0))
);

#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>

std::uintptr_t Global = reinterpret_cast<std::uintptr_t>(&RootWidget);

template <typename T>
void printPtr(T* InPtr)
{
    if(!InPtr)
    {
        std::cout << "nullptr (nullptr)\n";
        return;
    }
    
    std::uintptr_t AddressValue = reinterpret_cast<std::uintptr_t>(InPtr);
    std::cout << std::hex << InPtr << std::dec << " (" << AddressValue - Global << ")\n";
}

template <typename T>
void hexDump(const T& obj)
{
    const auto* Bytes = reinterpret_cast<const uint8*>(&obj);
    const size_t Size = sizeof(T);

    std::cout << "--- Memory Dump ---" << '\n';
    std::cout << "Type: " << typeid(T).name() << '\n';
    std::cout << "Size: " << Size << " bytes" << '\n';
    std::cout << "Start: "; printPtr(&obj);
    std::cout << "Data: ";
    
    for(size_t i = 0; i < Size; ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(Bytes[i]) << " ";
    
    std::cout << std::dec << "\n-------------------\n";
}

void ThePerfectAlgorithm(const void* JustPointer)
{
    const FWidgetBase* WidgetBasePtr = static_cast<const FWidgetBase*>(JustPointer);
    if(const SWidgetContainer<>* Container = Cast<SWidgetContainer<>>(WidgetBasePtr))
    {
        WidgetBasePtr += sizeof(SWidgetContainer<>);

        for(int i = 0; i < Container->ChildWidgetsCount; ++i)
        {
            while (WidgetBasePtr->LocalGUTID == 0) ++WidgetBasePtr;
            
            Reflection::Call(WidgetBasePtr, [&](auto& Widget)
            {
                // std::cout << typeid(Widget).name() << '\n';
                Widget.Render();
                WidgetBasePtr += sizeof(decltype(Widget));
            });
        }
    }
}

FWidgetBase* HoveredWidget = nullptr;
FWidgetBase* PressedWidget = nullptr;

int main()
{
    hexDump(RootWidget);
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    auto Window = SWindow()
        .SetSize(FUIntVector2D(1920, 1080))
        .SetTitle("Hello From Shoko! [SDL2]");
    RootWidget.SetSize(1920, 1080);
    
    Window.ActivateRenderContext();
    
    auto LastTime = std::chrono::high_resolution_clock::now();
    uint64 Time = 0;
    while(true)
    {
        FInputEvent InputEvent = FShokoInput::PullEvents();
        if(InputEvent.Key == EKey::Window_Close) break;
        
        {
            FWidgetBase* CurrentWidget = RootWidget.HitTest(FShokoInput::GetMousePosition());
            
            if(HoveredWidget != CurrentWidget)
            {
                if(HoveredWidget)
                    Reflection::Call(HoveredWidget, [&](auto& Widget)
                    {
                        Meta::TryCall(Widget, [](auto& CalledWidget) -> decltype(CalledWidget.CallOnUnhover()) { CalledWidget.CallOnUnhover(); });
                    });
                
                HoveredWidget = CurrentWidget;
                
                if(HoveredWidget)
                    Reflection::Call(HoveredWidget, [&](auto& Widget)
                    {
                        Meta::TryCall(Widget, [](auto& CalledWidget) -> decltype(CalledWidget.CallOnHover()) { CalledWidget.CallOnHover(); });
                    });
            }
            if(FShokoInput::IsMouseWasPressed(EMouseButton::Left))
            {
                PressedWidget = CurrentWidget;
                if(PressedWidget)
                {
                    Reflection::Call(PressedWidget, [&](auto& W)
                    {
                        Meta::TryCall(W, [](auto& CalledWidget) -> decltype(CalledWidget.CallOnMouseDown()) { CalledWidget.CallOnMouseDown(); });
                    });
                }
            }
            if(FShokoInput::IsMouseWasReleased(EMouseButton::Left))
            {
                if(PressedWidget)
                {
                    Reflection::Call(PressedWidget, [&](auto& Widget)
                    {
                        Meta::TryCall(Widget, [](auto& CalledWidget) -> decltype(CalledWidget.CallOnMouseUp()) { CalledWidget.CallOnMouseUp(); });
                    });

                    if(PressedWidget == CurrentWidget)
                    {
                        Reflection::Call(PressedWidget, [&](auto& Widget) {
                            Meta::TryCall(Widget, [](auto& CalledWidget) -> decltype(CalledWidget.CallOnClicked()) { CalledWidget.CallOnClicked(); });
                        });
                    }

                    PressedWidget = nullptr;
                }
            }
            
            // RootWidget.Get<5>().SetPosition(FShokoInput::GetMousePosition().X, FShokoInput::GetMousePosition().Y);
            // printPtr(Test);
        }
        
        FShokoRenderer::PreRender();
        FShokoRenderer::Fill(FColor(30, 30, 120));
        ThePerfectAlgorithm(&RootWidget);
        FShokoRenderer::PostRender();
        
        // auto EndTime = std::chrono::high_resolution_clock::now();
        // printf("FPS: %.2f\r", 1.0f / std::chrono::duration<float>(EndTime - LastTime).count());
        // fflush(stdout);
        // LastTime = EndTime;
        ++Time;
    }
    
    Window.Deinitialize();
    FShokoInput::Deinitialize();
    FShokoRenderer::Deinitialize();
    
    return 0;
}
