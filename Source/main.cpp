#include "Experimental.h"
#include "Shoko/Shoko.h"

using namespace Shoko;

void TestOnMouseUp1();
void TestOnMouseUp2();

auto RootWidget1 = SNew<SWidgetContainer>
(
    SNew<SButton>()
        .SetPosition(100, 200)
        .SetSize(200, 200)
        .OnMouseUp(&TestOnMouseUp1)
        .SetColor(FColor(255, 50, 50)),

    SNew<SBoxWidget>()
        .SetPosition(1920-10, 0)
        .SetSize(10, 10)
        .SetColor(FColor(255, 0, 0))
)
.SetSize(1000, 700);

auto RootWidget2 = SNew<SWidgetContainer>
(
    SNew<SButton>()
        .SetPosition(400, 200)
        .SetSize(200, 200)
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
)
.SetSize(1000, 700);

bool bLol;

void TestOnMouseUp1()
{
    printf("[1] Mouse Up\n");
    bLol = false;
}

void TestOnMouseUp2()
{
    printf("[2] Mouse Up\n");
    bLol = true;
}

#include <chrono>

int main()
{
    FShokoRenderer::Initialize();
    FShokoInput::Initialize();
    
    auto Window = SWindow()
        .SetSize(FUIntVector2D(1000, 700))
        .SetTitle("Shoko - Compile-time UI Framework [FShokoRenderer Demo]");
    RootWidget2.SetSize(1000, 700);
    Window.ActivateRenderContext();
    
    auto LastTime = std::chrono::high_resolution_clock::now();
    uint64 Time = 0;
    while(true)
    {
        if(FShokoInput::PullEvents().Key == EKey::Window_Close) break;
        
        Experimental::TestMouseSystem(bLol ? RootWidget1.HitTest(FShokoInput::GetMousePosition()) : RootWidget2.HitTest(FShokoInput::GetMousePosition()));
        // RootWidget2.Get<0>().SetPosition(FShokoInput::GetMousePosition().X, FShokoInput::GetMousePosition().Y);
        
        FColor BackgroundColor = FColor::FromHex(0x1E1B1DFF);
        FShokoRenderer::PreRender();
        FShokoRenderer::Fill(BackgroundColor);
        Experimental::ThePerfectAlgorithm(bLol ? static_cast<const void*>(&RootWidget1) : static_cast<const void*>(&RootWidget2));
        FShokoRenderer::PostRender();
        
        /*
        FShokoRenderer::PreRender();
        {
            FColor BackgroundColor = FColor::FromHex(0x1E1B1DFF);
            FColor PanelColor      = FColor::FromHex(0x2C272AFF);
            FColor AccentColor     = FColor::FromHex(0xC8A3B0FF);
            FColor TextPrimary     = FColor::FromHex(0xD8D3D6FF);
            FColor AccentHover     = FColor::FromHex(0xD6B1BDFF);

            
            // ------------------------------------------
            // 1. BASE: Fill, DrawLine, DrawArc
            // ------------------------------------------
            FShokoRenderer::Fill(BackgroundColor);
            FShokoRenderer::DrawLine(FLocation(20, 20), FLocation(980, 20), AccentColor, 2); // Горизонтальный разделитель
            FShokoRenderer::DrawArc(FLocation(950, 650), 40, FAngle::FromDegrees(180), FAngle::FromDegrees(270), AccentColor, 5, EShokoRendererBorderType::Outside);


            // ------------------------------------------
            // 2. RECT: DrawRect, DrawRectBorder
            // ------------------------------------------
            FShokoRenderer::DrawRect(FLocation(50, 50), FSize(150, 100), PanelColor); // Залитый прямоугольник
            FShokoRenderer::DrawRectBorder(FLocation(250, 50), FSize(150, 100), AccentColor, 3, EShokoRendererBorderType::Inside);


            // ------------------------------------------
            // 3. ROUNDED RECT: DrawRoundedRect, DrawRoundedRectBorder
            // ------------------------------------------
            FShokoRenderer::DrawRoundedRect(FLocation(50, 180), FSize(150, 100), 15, PanelColor);
            FShokoRenderer::DrawRoundedRectBorder(FLocation(250, 180), FSize(150, 100), 15, AccentColor, 3, EShokoRendererBorderType::Outside);


            // ------------------------------------------
            // 4. CIRCLE: DrawCircle, DrawCircleBorder
            // ------------------------------------------
            FShokoRenderer::DrawCircle(FLocation(125, 350), 50, PanelColor);
            FShokoRenderer::DrawCircleBorder(FLocation(325, 350), 50, AccentColor, 3, EShokoRendererBorderType::Inside);


            // ------------------------------------------
            // 5. ELLIPSE: DrawEllipse, DrawEllipseBorder
            // ------------------------------------------
            FShokoRenderer::DrawEllipse(FLocation(125, 480), FSize(70, 40), PanelColor);
            FShokoRenderer::DrawEllipseBorder(FLocation(325, 480), FSize(70, 40), AccentColor, 2, EShokoRendererBorderType::Outside);


            // ------------------------------------------
            // 6. CIRCLE SECTOR: DrawCircleSector, DrawCircleSectorBorder
            // ------------------------------------------
            FShokoRenderer::DrawCircleSector(FLocation(125, 620), 50, FAngle::FromDegrees(0), FAngle::FromDegrees(135), PanelColor);
            FShokoRenderer::DrawCircleSectorBorder(FLocation(325, 620), 50, FAngle::FromDegrees(180), FAngle::FromDegrees(300), AccentColor, 3, EShokoRendererBorderType::Outside);


            // ------------------------------------------
            // 7. BEZIER: DrawQuadraticBezier, DrawCubicBezier
            // ------------------------------------------
            FShokoRenderer::DrawQuadraticBezier(FLocation(500, 50), FLocation(600, 150), FLocation(700, 50), AccentColor);
            FShokoRenderer::DrawCubicBezier(FLocation(500, 200), FLocation(550, 300), FLocation(650, 100), FLocation(700, 200), AccentColor);


            // ------------------------------------------
            // 8. POLYGON: DrawPolygonBorder
            // ------------------------------------------
            TStaticArray<FLocation, 3> TrianglePoints =
            {
                FLocation(500, 400),
                FLocation(600, 500),
                FLocation(400, 500)
            };
            FShokoRenderer::DrawPolygonBorder<3>(TrianglePoints, AccentColor, 3, EShokoRendererBorderType::Inside);


            // ------------------------------------------
            // 9. PATH: DrawPath
            // ------------------------------------------
            TStaticArray<FLocation, 5> WavePoints =
            {
                FLocation(750, 400),
                FLocation(800, 450),
                FLocation(850, 400),
                FLocation(900, 450),
                FLocation(950, 400)
            };
            FShokoRenderer::DrawPath<5>(WavePoints, AccentColor, 2);
        }
        
        FShokoRenderer::PostRender();
        */
        
        // auto EndTime = std::chrono::high_resolution_clock::now();
        // printf("FPS: %.2f\r", 1.0f / std::chrono::duration<float>(EndTime - LastTime).count());
        fflush(stdout);
        // LastTime = EndTime;
        ++Time;
    }
    
    Window.Deinitialize();
    FShokoInput::Deinitialize();
    FShokoRenderer::Deinitialize();
    
    return 0;
}
