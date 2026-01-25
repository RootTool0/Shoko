#pragma once

#include <iomanip>
#include <iostream>

#include "Input.h"
#include "Shoko.h"
#include "Types/InputEvent.h"
#include "Widgets/WidgetContainer.h"

/*
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

constexpr auto RootWidget = SNew<SWidgetContainer>
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
        .SetPosition(1, 1)
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
*/

namespace Shoko
{
    class FWidgetBase;
}

namespace Shoko
{
    namespace Experimental
    {
        
        // std::uintptr_t Global = reinterpret_cast<std::uintptr_t>(&RootWidget);
        inline std::uintptr_t Global = 0;
        
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
        
        inline void ThePerfectAlgorithm(const void* JustPointer)
        {
            const FWidgetBase* WidgetBasePtr = static_cast<const FWidgetBase*>(JustPointer);
            if(const SWidgetContainer<>* Container = Cast<SWidgetContainer<>>(WidgetBasePtr))
            {
                WidgetBasePtr += sizeof(SWidgetContainer<>);

                for(int i = 0; i < Container->ChildWidgetsCount; ++i)
                {
                    while (WidgetBasePtr->LocalGUTID == 0) ++WidgetBasePtr;
            
                    Reflection::ForEachWidget(WidgetBasePtr, [&](auto& Widget)
                    {
                        // std::cout << typeid(Widget).name() << '\n';
                        Widget.Render();
                        WidgetBasePtr += sizeof(decltype(Widget));
                    });
                }
            }
        }
        
        inline const FWidgetBase* HoveredWidget = nullptr;
        inline const FWidgetBase* PressedWidget = nullptr;
        inline const FWidgetBase* FocusedWidget = nullptr;
        
        inline void TestMouseSystem(const FWidgetBase* CurrentWidget)
        {
            // FWidgetBase* CurrentWidget = RootWidget.HitTest(FShokoInput::GetMousePosition());
            
            if(HoveredWidget != CurrentWidget)
            {
                if(HoveredWidget)
                    Reflection::ForEachWidget(HoveredWidget, [&](auto& Widget)
                    {
                        if constexpr (SHOKO_REFLECTION_HAS_METHOD(Widget, CallOnUnhover)) Widget.CallOnUnhover();
                    });
                
                HoveredWidget = CurrentWidget;
                
                if(HoveredWidget)
                    Reflection::ForEachWidget(HoveredWidget, [&](auto& Widget)
                    {
                        if constexpr (SHOKO_REFLECTION_HAS_METHOD(Widget, CallOnHover)) Widget.CallOnHover();
                    });
            }
            
            if(PressedWidget)
                Reflection::ForEachWidget(PressedWidget, [&](auto& Widget)
                {
                    if constexpr (SHOKO_REFLECTION_HAS_METHOD(Widget, CallOnMouseMove)) Widget.CallOnMouseMove();
                });
            
            if(FShokoInput::IsMouseWasPressed(EMouseButton::Left))
            {
                PressedWidget = CurrentWidget;
                FocusedWidget = CurrentWidget;
                if(PressedWidget)
                    Reflection::ForEachWidget(PressedWidget, [&](auto& Widget)
                    {
                        if constexpr (SHOKO_REFLECTION_HAS_METHOD(Widget, CallOnMouseDown)) Widget.CallOnMouseDown();
                    });
            }
            
            if(FShokoInput::IsMouseWasReleased(EMouseButton::Left))
            {
                if(PressedWidget)
                {
                    Reflection::ForEachWidget(PressedWidget, [&](auto& Widget)
                    {
                        if constexpr (SHOKO_REFLECTION_HAS_METHOD(Widget, CallOnMouseUp)) Widget.CallOnMouseUp();
                    });

                    PressedWidget = nullptr;
                }
            }
            
            if(FocusedWidget && !FShokoInput::GetInputEvent().bRepeat)
            {
                Reflection::ForEachWidget(FocusedWidget, [&](auto& Widget)
                {
                    if constexpr (SHOKO_REFLECTION_HAS_METHOD(Widget, CallOnKey))
                        Widget.CallOnKey(FShokoInput::GetInputEvent().Key);
                });
            }
            
            // RootWidget.Get<5>().SetPosition(FShokoInput::GetMousePosition().X, FShokoInput::GetMousePosition().Y);
            // printPtr(Test);
        }
    }
}
