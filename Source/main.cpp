#include <SDL.h>
#include <iostream>
#include <string>

#include "Shoko/BoxWidget.h"
#include "Shoko/Button.h"
#include "Shoko/Shoko.h"
#include "Shoko/WidgetContainer.h"
#include "Shoko/Types/Color.h"

using namespace Shoko;

/*
*static_assert(has_method_Draw<T>, R"(
[Shoko]
Похоже, ваш виджет не умеет рисоваться...
Не забыли ли вы реализовать метод Draw()?
)");

static_assert(is_constexpr_constructible<T>, R"(
[Shoko]
Ваш виджет не может быть создан на этапе компиляции...
Проверьте, все ли его поля инициализируются constexpr?
)");
static_assert(
    !Meta::IsContainer<TWidget> || Meta::HasChildren<TWidget>,
    "Контейнер без детей — одиночество, которому мы не можем помочь."
);

*/

template<typename TRootWidget>
class TestUIManager
{
    const TRootWidget* RootWidget = nullptr;
    const FWidgetBase* LastHovered = nullptr;
    
public:
    explicit TestUIManager(const TRootWidget& root) : RootWidget(&root) {}
    
    void UpdateHover(int16 MouseX, int16 MouseY)
    {
        const FWidgetBase* currentHovered = RootWidget->GetWidgetAt(MouseX, MouseY);
        
        if (currentHovered == LastHovered) return;

        if (LastHovered)
            if (auto* old = Cast<SButton>(LastHovered))
                old->CallOnUnhover();
        
        if (currentHovered)
            if (auto* cur = Cast<SButton>(currentHovered))
                cur->CallOnHover();

        LastHovered = currentHovered;
    }
    
    void RenderAll(SDL_Renderer* renderer) const
    {
        RootWidget->Render(renderer);
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

int main()
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
            .SetPosition(300, 200)
            .SetSize(100, 100)
            .SetColor(FColor(255, 255, 255))
    );
    
    /*
    std::cout << std::to_string(RootWidget.GUTID) << '\n';
    std::cout << std::to_string(RootWidget.GetChildByIndex<0>().GUTID) << '\n';
    std::cout << std::to_string(RootWidget.GetChildByIndex<1>().GUTID) << '\n';
    std::cout << std::to_string(RootWidget.GetChildByIndex<2>().GUTID) << '\n';
    */
    
    //const int16* test = &RootWidget.GetChildByIndex<2>().X;
    
    /*
    volatile constexpr int i = 32;
    volatile int* p = (int*)&i;
    *p = 64;
    
    std::cout << "i = " << i << '\n';
    std::cout << "*p = " << *p << '\n';
    */
    
    const SButton* btn = &RootWidget.GetChildByIndex<0>();
    std::cout << std::to_string(btn->GUTID) << '\n';
    std::cout << std::to_string(btn->LocalGUTID) << '\n';

    std::cout << "=====\n";
    
    const GUTID_t pId = static_cast<const FWidgetBase*>(btn)->LocalGUTID;
    std::cout << std::to_string(pId) << '\n';
    
    
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

        const FWidgetBase* currentHovered = RootWidget.GetWidgetAt(MouseX, MouseY);
        // std::cout << std::to_string(currentHovered->LocalGUTID) << '\n';
        
        // int16* x = const_cast<int16*>(&RootWidget.GetChildByIndex<0>().Y);
        // *x = 200 + static_cast<int16>(40 * sin(SDL_GetTicks() / 100.0));
        
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
