#include <SDL.h>
#include <iostream>

#include "Shoko/BoxWidget.h"
#include "Shoko/Button.h"
#include "Shoko/Shoko.h"
#include "Shoko/WidgetContainer.h"
#include "Shoko/Types/Color.h"

using namespace Shoko;

// РџСЂРѕРІРµСЂРєР° РЅР°Р»РёС‡РёСЏ РјРµС‚РѕРґР° CallOnHover
template<typename T, typename = void>
struct HasCallOnHover : std::false_type {};

template<typename T>
struct HasCallOnHover<T, std::void_t<decltype(std::declval<T>().CallOnHover())>> : std::true_type {};

// РџСЂРѕРІРµСЂРєР° РЅР°Р»РёС‡РёСЏ РјРµС‚РѕРґР° CallOnUnhover
template<typename T, typename = void>
struct HasCallOnUnhover : std::false_type {};

template<typename T>
struct HasCallOnUnhover<T, std::void_t<decltype(std::declval<T>().CallOnUnhover())>> : std::true_type {};

template<typename T>
void CallHoverIfExists(const void* widgetPtr)
{
    if (!widgetPtr) return;

    const T* w = static_cast<const T*>(widgetPtr);
    if constexpr (HasCallOnHover<T>::value)
        w->CallOnHover();
}

template<typename T>
void CallUnhoverIfExists(const void* widgetPtr)
{
    if (!widgetPtr) return;

    const T* w = static_cast<const T*>(widgetPtr);
    if constexpr (HasCallOnUnhover<T>::value)
        w->CallOnUnhover();
}

class TestLMAO
{
};

template<typename TRootWidget>
class TestUIManager
{
    const TRootWidget* RootWidget;
    const void* LastHovered = nullptr;
    
public:
    TestUIManager(const TRootWidget& root) 
        : RootWidget(&root) 
    {}
    
    void UpdateHover(int16 MouseX, int16 MouseY)
    {
        const auto* currentHovered = RootWidget->GetWidgetAt(MouseX, MouseY);
        
        if (currentHovered == LastHovered)
            return;
        
        if (LastHovered)
        {
            if (auto* oldButton = TryCast<SButton>(LastHovered))
            {
                oldButton->CallOnUnhover();
            }
        }
        
        if (currentHovered)
        {
            if (auto* newButton = TryCast<SButton>(currentHovered))
            {
                newButton->CallOnHover();
            }
        }
        
        LastHovered = currentHovered;
    }
    
    void RenderAll(SDL_Renderer* renderer) const
    {
        RootWidget->Render(renderer);
    }
    
private:
    template<typename T>
    static const T* TryCast(const void* ptr)
    {
        if (!ptr) return nullptr;
        return static_cast<const T*>(ptr);
    }
};


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

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* SDLWindow = SDL_CreateWindow("Hi, Shoko!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!SDLWindow)
    {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!SDLRenderer)
    {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(SDLWindow);
        SDL_Quit();
        return 1;
    }

    SDL_Event SDLEvent;
    
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
            .SetPosition(250, 200)
            .SetSize(200, 200)
            .SetColor(FColor(255, 255, 255))
    );
    
    auto& test = RootWidget.GetChildByIndex<2>();
    
    // static_assert(RootWidget.GetChildByIndex<0>().GetColor() == FColor(255, 50, 50), "Test");
    
    TestUIManager ui(RootWidget);
    
    bool bRunning = true;
    while(bRunning)
    {
        while(SDL_PollEvent(&SDLEvent))
        {
            if(SDLEvent.type == SDL_QUIT) bRunning = false;
        }
        
        int MouseX = -1, MouseY = -1;
        SDL_GetMouseState(&MouseX, &MouseY);
        ui.UpdateHover(MouseX, MouseY);
        
        // const auto* hovered = RootWidget.GetWidgetAt(MouseX, MouseY);
        // if (hovered) {
        //     std::cout << "Hovered widget at: " << MouseX << ", " << MouseY << std::endl;
        // }
        
        SDL_SetRenderDrawColor(SDLRenderer, 30, 30, 120, 255);
        SDL_RenderClear(SDLRenderer);
        ui.RenderAll(SDLRenderer);
        SDL_RenderPresent(SDLRenderer);
    }
    
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();

    return 0;
}
