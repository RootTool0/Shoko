#include "Shoko.h"
#include "Experimental.h"
#include "Demo.h"

using namespace Shoko;

uint8 Value = 0;
TStringFixed<32> ResultText;

void UpdateBinaryResult()
{
    ResultText.Empty();
    char buffer[32];
    
    ResultText += "Result: ";
    snprintf(buffer, sizeof(buffer), "%d", Value);
    ResultText += buffer;
    
    ResultText += " (0x";
    snprintf(buffer, sizeof(buffer), "%02X", Value);
    ResultText += buffer;
    ResultText += ")";

    std::cout << ResultText << '\n';
}

void OnBitChanged(uint8 BitIndex, bool bValue)
{
    if(bValue) Value |= (1 << BitIndex);
    else Value &= ~(1 << BitIndex);
    UpdateBinaryResult();
}

constexpr auto RootWidget =
    SNew<SRootContainer>(
        SNew<SPaddingBox>(
            SNew<SRect>()
                .SetColor(FStyle::BackgroundPanel)
        )
        .SetPadding(FPadding(24)),
        
        SNew<SPaddingBox>(
            SNew<SHorizontalBox>(
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(7, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(6, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(5, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(4, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(3, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(2, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(1, bValue); })),
                SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(0, bValue); }))
            )
        )
        .SetPadding(FPadding(48))
    )
    .SetSize(FSize(480, 320));
    

int main()
{
    Experimental::hexDump(RootWidget);
    
    auto Window = SWindow()
        .SetSize(FSize(480, 320))
        .SetTitle("Shoko - Compile-time UI Framework");
    Window.ActivateRenderContext();
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    UpdateBinaryResult();
    
    while(true)
    {
        if(FShokoInput::PullEvents().Key == FInputEvent::GetKey(ESystemKey::Window_Close)) break;
        
        Experimental::TestMouseSystem(RootWidget.HitTest(FShokoInput::GetMousePosition()));
        
        FShokoRenderer::PreRender();
        {
            FShokoRenderer::Fill(FStyle::Background);
            RootWidget.Render();
        }
        FShokoRenderer::PostRender();
        
        Demo::ShowFPS();
    }
    
    Window.Deinitialize();
    FShokoInput::Deinitialize();
    FShokoRenderer::Deinitialize();
    
    return 0;
}
