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
}

void OnBitChanged(uint8 BitIndex, bool bValue)
{
    if(bValue) Value |= (1 << BitIndex);
    else Value &= ~(1 << BitIndex);
    UpdateBinaryResult();
}

TStringBuffer<12> TextInputBuffer;

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
                SNew<SCenterBox>(
                    SNew<STextInput>()
                        .SetTextBuffer(&TextInputBuffer)
                        .SetTextSize(32)
                        .SetTextColor(FStyle::Border)
                        .SetBackgroundColor(FStyle::ActionDisabled)
                        .SetSize(FSize(315, 40))
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
        if(FShokoInput::PullEvents().Key == FInputEvent::GetKey(ESystemKey::Window_Close)) break;
        
        Experimental::TestMouseSystem(RootWidget.HitTest(FShokoInput::GetMousePosition()));
        
        FShokoRenderer::PreRender();
        {
            FShokoRenderer::Fill(FStyle::Background);
            RootWidget.Render();
        }
        FShokoRenderer::PostRender();

        // Demo::ShowFPS();
    }
    
    Window.Deinitialize();
    FShokoInput::Deinitialize();
    FShokoRenderer::Deinitialize();
    
    return 0;
}
