#include "Shoko.h"
#include "Experimental.h"
#include "Demo.h"

#include "Types/StaticPool/StaticPool.h"
#include "Widgets/WidgetPoolView.h"

using namespace Shoko;

TStaticPool<SCheckBox, 8> Pool;
int X = 0;

constexpr auto RootWidget =
    SNew<SRootContainer>(
        SNew<SPaddingBox>(
            SNew<SRootContainer>(
                SNew<SRoundRect>()
                .SetRadius(24)
                .SetColor(FStyle::BackgroundPanel),
                
                SNew<SPaddingBox>(
                    SNew<SHorizontalBox>(
                        SNew<SButton>()
                        .OnMouseUp([]()
                        {
                            if(Pool.RemoveLast())
                                X -= 50;
                        }),
                        
                        SNew<SButton>()
                        .OnMouseUp([]()
                        {
                            if(Pool.Add(SNew<SCheckBox>().SetLocation(FLocation(0, X))))
                                X += 50;
                        })
                    )
                )
                .SetPadding(FPadding(128))
            )
        )
        .SetPadding(FPadding(24)),

        SNew<SWidgetPoolView<SCheckBox>>()
            .Bind(Pool)
    )
    .SetSize(FSize(1200, 700));

const char* Shader = R"(
#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform float uTime;

void main()
{         
    vec3 Col = 0.5 + 0.5 * cos(uTime + vUV.xyx + vec3(0, 2, 4));

    FragColor = vec4(Col, 1.0);
}
)";

int main()
{
    Experimental::hexDump(RootWidget);
    
    auto Window = SWindow()
        .SetSize(FSize(1200, 700))
        .SetTitle("Shoko - Compile-time UI Framework");
    Window.ActivateRenderContext();
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    // RootWidget.Get<1>().ChildWidget.SetShaderProgram(FShokoRenderer::CompileShader(Shader));
    
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
