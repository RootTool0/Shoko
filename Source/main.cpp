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

constexpr auto RootWidget =
    SNew<SRootContainer>(
        SNew<SPaddingBox>(
            SNew<SRoundRect>()
                .SetRadius(12)
                .SetColor(FStyle::BackgroundPanel)
        )
        .SetPadding(FPadding(24)),
        
        SNew<SPaddingBox>(
            SNew<SRootContainer>(
                SNew<SVerticalBox>(
                    SNew<SCenterBox>(
                        SNew<SText>()
                            .SetText("BINARY TO DECIMAL")
                            .SetTextSize(32)
                            .SetColor(FStyle::Action)
                    ),
                    
                    SNew<SHorizontalBox>(
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(7, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("128"))
                        ),
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(6, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("64"))
                        ),    
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(5, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("32"))
                        ),    
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(4, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("16"))
                        ),    
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(3, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("8"))
                        ),    
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(2, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("4"))
                        ),
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(1, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("2"))
                        ),
                        SNew<SVerticalBox>(
                            SNew<SCenterBox>(SNew<SCheckBox>().SetSize(FSize(36)).OnValueChanged([](bool bValue){ OnBitChanged(0, bValue); })),
                            SNew<SCenterBox>(SNew<SText>().SetColor(FStyle::ActionDisabled).SetText("1"))
                        )
                    ),
                    
                    SNew<SCenterBox>(
                        SNew<SText>()
                            .SetText(ResultText)
                            .SetTextSize(14)
                            .SetColor(FStyle::ActionHighlight)
                    )
                )
            )
        )
        .SetPadding(FPadding(48))
    )
    .SetSize(FSize(480, 320));

int main()
{
    Experimental::hexDump(RootWidget);
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    auto Window = SWindow()
        .SetSize(FSize(480, 320))
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
