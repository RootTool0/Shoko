#include "Shoko.h"
#include "Experimental.h"
#include "Demo.h"

using namespace Shoko;

uint8 Value = 0;
TStringFixed<32> ResultText;

void UpdateBinaryResult()
{
    ResultText.Empty();
    ResultText += "Result: ";
    ResultText += TextFormat("%d", Value); 
    
    ResultText += " (0x";
    ResultText += TextFormat("%02X", Value);
    ResultText += ")";
}

void OnBitChanged(uint8 BitIndex, bool bValue)
{
    if(bValue) Value |= (1 << BitIndex);
    else Value &= ~(1 << BitIndex);
    UpdateBinaryResult();
}

/*
constexpr auto RootWidget =
    SNew<SCenterBox>(
        SNew<SPaddingBox>(
            SNew<SRoundRect>()
                .SetRadius(24)
                .SetColor(FStyle::BackgroundPanel)
        )
        .SetPadding(FPadding(12, 12))
    ).SetSize(FSize(1024, 512));
    */
    
/*
constexpr auto RootWidget = SNew<SWidgetContainer>(
    SNew<SCenterBox>(
        SNew<SPaddingBox>(
            SNew<SRoundRect>()
                // .SetRadius(24)
                .SetColor(FStyle::BackgroundPanel)
        )
        .SetPadding(FPadding(24, 24))
    ),
    
    SNew<SText>()
        .SetText("BINARY TO DECIMAL")
        .SetLocation(FLocation(340, 160))
        .SetSize(32)
        .SetColor(FStyle::Action),
    
    SNew<SCheckBox>().SetLocation(FLocation(278, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(7, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(338, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(6, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(398, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(5, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(458, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(4, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(518, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(3, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(578, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(2, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(638, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(1, bValue); }),
    SNew<SCheckBox>().SetLocation(FLocation(698, 208)).SetSize(FSize(48)).OnValueChanged([](bool bValue){ OnBitChanged(0, bValue); }),

    SNew<SText>().SetLocation(FLocation(284, 268)).SetColor(FStyle::ActionDisabled).SetText("128"),
    SNew<SText>().SetLocation(FLocation(350, 268)).SetColor(FStyle::ActionDisabled).SetText("64"),
    SNew<SText>().SetLocation(FLocation(410, 268)).SetColor(FStyle::ActionDisabled).SetText("32"),
    SNew<SText>().SetLocation(FLocation(472, 268)).SetColor(FStyle::ActionDisabled).SetText("16"),
    SNew<SText>().SetLocation(FLocation(539, 268)).SetColor(FStyle::ActionDisabled).SetText("8"),
    SNew<SText>().SetLocation(FLocation(599, 268)).SetColor(FStyle::ActionDisabled).SetText("4"),
    SNew<SText>().SetLocation(FLocation(659, 268)).SetColor(FStyle::ActionDisabled).SetText("2"),
    SNew<SText>().SetLocation(FLocation(719, 268)).SetColor(FStyle::ActionDisabled).SetText("1"),
    
    SNew<SText>()
        .SetText(ResultText)
        .SetLocation(FLocation(400, 320))
        .SetSize(26)
        .SetColor(FStyle::ActionHighlight)
)
.SetSize(FSize(1024, 512));
*/

constexpr auto RootWidget = SNew<SHorizontalBox>(
    SNew<SRect>()
        .SetColor(FColor(255, 0, 0)),

    SNew<SPaddingBox>(
        SNew<SRect>()
            .SetColor(FColor(0, 0, 255))
    )
    .SetPadding(FPadding(12, 48)),

    SNew<SVerticalBox>(
        SNew<SCenterBox>(
            SNew<SRect>()
                .SetColor(FColor(255, 0, 255))
                .SetSize(FSize(24, 24))
        ),
        SNew<SRect>()
            .SetColor(FColor(0, 255, 0))
    )
)
.SetSize(FSize(1024, 512));


int main()
{
    Experimental::hexDump(RootWidget);
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    auto Window = SWindow()
        .SetSize(FSize(1024, 512))
        .SetTitle("Shoko - Compile-time UI Framework");
    
    UpdateBinaryResult();
    
    while(true)
    {
        if(FShokoInput::PullEvents().Key == EKey::Window_Close) break;
        
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
