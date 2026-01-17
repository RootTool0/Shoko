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
                std::cout << typeid(Widget).name() << '\n';
                Widget.Render();
                WidgetBasePtr += sizeof(decltype(Widget));
            });
        }
    }
}

int main()
{
    std::cout << typeid(Reflection::GetClassByGUTID<0>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<1>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<2>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<3>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<4>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<5>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<6>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<7>()).name() << '\n';
    std::cout << typeid(Reflection::GetClassByGUTID<8>()).name() << '\n';
    
    hexDump(RootWidget);
    
    FShokoRenderer::Initialize();
    
    auto Window = SWindow()
        .SetSize(FUIntVector2D(1920, 1080))
        .SetTitle("Hello From Shoko! [SDL2]");
    
    Window.ActivateRenderContext();
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    uint64 Time = 0; 
    while (true)
    {
#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2
        SDL_Event event;
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                break;
#endif
        
        auto startTime = std::chrono::high_resolution_clock::now();
        
        FShokoRenderer::PreRender();
        FShokoRenderer::Fill(FColor(30, 30, 120));
        ThePerfectAlgorithm(&RootWidget);
        FShokoRenderer::PostRender();
        
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = endTime - lastTime;
        lastTime = endTime;
        
        printf("FPS: %.2f\r", 1.0f / delta.count());
        fflush(stdout);

        ++Time;
    }
    
    Window.Deinitialize();
    
    return 0;
}
