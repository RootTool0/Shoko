
#include <iomanip>
#include <iostream>

#include "Shoko/Shoko.h"

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

/*
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
*/

template <typename T>
void hexDump(const T& obj) {
    // Используем std::uint8_t для работы с сырыми байтами
    const auto* bytes = reinterpret_cast<const std::uint8_t*>(&obj);
    const size_t size = sizeof(T);

    std::cout << "--- Memory Dump ---" << std::endl;
    std::cout << "Type: " << typeid(T).name() << "\n";
    std::cout << "Size: " << size << " bytes" << "\n";
    std::cout << "Data: ";

    // Форматированный вывод HEX
    for (size_t i = 0; i < size; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(bytes[i]) << " ";
    }
    
    std::cout << std::dec << std::endl << "-------------------\n" << std::endl;
}

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


constexpr auto CachedWidget = SNew<SWidgetContainer>
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
        .SetColor(FColor(255, 255, 255)) //,

    // SNew<SOpenGLContext>()
    //     .SetPosition(300, 300)
    //     .SetSize(100, 100)
);

int main()
{
    auto RootWidget = CachedWidget;

    hexDump(RootWidget);
    hexDump(RootWidget.GetChildByIndex<0>());
    
    auto& test = RootWidget.GetChildByIndex<2>();
    
    hexDump(RootWidget.GetChildByIndex<1>());
    hexDump(RootWidget.GetChildByIndex<2>());
    
    // static_assert(sizeof(RootWidget) == -1);
    
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
    
    /*
    const SButton* btn = &RootWidget.GetChildByIndex<0>();
    std::cout << std::to_string(btn->GUTID) << '\n';
    std::cout << std::to_string(btn->LocalGUTID) << '\n';

    std::cout << "=====\n";
    
    const GUTID_t pId = static_cast<const FWidgetBase*>(btn)->LocalGUTID;
    std::cout << std::to_string(pId) << '\n';
    */
    
    
    // TestUIManager ui(RootWidget);
    FShokoRenderer::Initialize();
    
    const char* VS = R"(
    #version 120
    void main()
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    }
    )";

    const char* FS = R"(
    #version 120
    void main()
    {
        gl_FragColor = gl_Color;
    }
    )";
    
    // GLuint Program = FShokoRenderer::CreateGLSLProgram(VS, FS);
    // glUseProgram(Program);
    
    while(FShokoRenderer::MainLoop())
    {
        // int MouseX = -1, MouseY = -1;
        // SDL_GetMouseState(&MouseX, &MouseY);
        // ui.UpdateHover(MouseX, MouseY);

        // const FWidgetBase* currentHovered = RootWidget.GetWidgetAt(MouseX, MouseY);
        // std::cout << std::to_string(currentHovered->LocalGUTID) << '\n';
        
        // int16* x = const_cast<int16*>(&RootWidget.GetChildByIndex<0>().Y);
        // *x = 200 + static_cast<int16>(40 * sin(SDL_GetTicks() / 100.0));
        
        // const auto* hovered = RootWidget.GetWidgetAt(MouseX, MouseY);
        // if (hovered) {
        //     std::cout << "Hovered widget at: " << MouseX << ", " << MouseY << std::endl;
        // }
        
        // test.SetColor(FColor(128 + sin(SDL_GetTicks() / 100.f) * 128, 0, 0));
        
        FShokoRenderer::PreRender();
        RootWidget.Render();
        FShokoRenderer::PostRender();
        // ui.RenderAll(SDLRenderer);
    }

    FShokoRenderer::Deinitialize();
    
    return 0;
}
