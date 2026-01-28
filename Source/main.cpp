#include "Shoko.h"
#include "Experimental.h"
#include "Demo.h"

using namespace Shoko;

uint32 ShaderID = 0;

constexpr auto RootWidget =
    SNew<SVerticalBox>(
        SNew<SOpenGLContext>(),
        
        SNew<SPaddingBox>(
            SNew<SRootBox>(
                SNew<SRoundRect>()
                .SetRadius(24)
                .SetColor(FStyle::BackgroundPanel),

                SNew<SCenterBox>(
                    SNew<SSlider>().OnValueChange([](float Alpha)
                    {
                        FShokoRenderer::SetShaderUniform1f(ShaderID, "uTest", Alpha);
                    })
                )
            )
        )
        .SetPadding(FPadding(24))
    )
    .SetSize(FSize(700, 1024));

const char* Shader = R"(
#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform float uTime;

uniform float uTest;

void main()
{         
    vec3 Col = 0.5 + 0.5 * cos(uTime + vUV.xyx + vec3(0, 2, 4));

    FragColor = vec4(Col, 1.0) * uTest;
}
)";

int main()
{
    Experimental::hexDump(RootWidget);
    
    auto Window = SWindow()
        .SetSize(FSize(700, 1024))
        .SetTitle("Shoko - Compile-time UI Framework");
    Window.ActivateRenderContext();
    
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    ShaderID = FShokoRenderer::CompileShader(Shader);
    RootWidget.Get<0>().SetShaderProgram(ShaderID);
    
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
