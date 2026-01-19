#pragma once

#include "Renderer.h"
#include "Types/Angle.h"
#include "Types/Color.h"

namespace Shoko
{
    namespace Demo
    {
        inline void AllPrimitives()
        {
            FShokoRenderer::PreRender();
            {
                FColor BackgroundColor = FColor::FromHex(0x1E1B1DFF);
                FColor PanelColor      = FColor::FromHex(0x2C272AFF);
                FColor AccentColor     = FColor::FromHex(0xC8A3B0FF);
                
                
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
        }
        
        inline void TestUI()
        {
            FShokoRenderer::PreRender();
            {
                // -------------------------------------------------
                // Colors
                // -------------------------------------------------
                FColor Background = FColor::FromHex(0x1E1B1DFF);
                FColor Panel      = FColor::FromHex(0x2C272AFF);
                FColor PanelDark  = FColor::FromHex(0x252124FF);
                FColor Border     = FColor::FromHex(0x3A3337FF);
                FColor Accent     = FColor::FromHex(0xC8A3B0FF);
                FColor AccentSoft = FColor::FromHex(0xD6B1BDFF);
                FColor Disabled   = FColor::FromHex(0x6C676AFF);

                // -------------------------------------------------
                // Background
                // -------------------------------------------------
                FShokoRenderer::Fill(Background);

                // -------------------------------------------------
                // Top Bar
                // -------------------------------------------------
                FShokoRenderer::DrawRect(FLocation(0, 0), FSize(1000, 60), PanelDark);
                FShokoRenderer::DrawLine(FLocation(0, 60), FLocation(1000, 60), Border, 1);

                // Window controls (mac-like)
                FShokoRenderer::DrawCircle(FLocation(20, 30), 6, Accent);
                FShokoRenderer::DrawCircle(FLocation(40, 30), 6, Disabled);
                FShokoRenderer::DrawCircle(FLocation(60, 30), 6, Disabled);

                // Toolbar buttons
                FShokoRenderer::DrawRoundedRect(FLocation(120, 15), FSize(80, 30), 6, Panel);
                FShokoRenderer::DrawRoundedRectBorder(FLocation(120, 15), FSize(80, 30), 6, Border, 1, EShokoRendererBorderType::Inside);

                FShokoRenderer::DrawRoundedRect(FLocation(210, 15), FSize(80, 30), 6, Accent);
                FShokoRenderer::DrawRoundedRect(FLocation(300, 15), FSize(80, 30), 6, Panel);

                // -------------------------------------------------
                // Sidebar
                // -------------------------------------------------
                FShokoRenderer::DrawRect(FLocation(0, 60), FSize(80, 640), Panel);
                FShokoRenderer::DrawLine(FLocation(80, 60), FLocation(80, 700), Border, 1);

                // Sidebar icons
                for(int16 i = 0; i < 5; ++i)
                {
                    int16 y = 90 + i * 70;
                    FShokoRenderer::DrawRoundedRect(FLocation(15, y), FSize(50, 50), 10, i == 1 ? Accent : PanelDark);
                    if(i == 1) FShokoRenderer::DrawRect(FLocation(0, y), FSize(4, 50), Accent);
                }

                // -------------------------------------------------
                // Main Panel
                // -------------------------------------------------
                FShokoRenderer::DrawRoundedRect(FLocation(100, 80), FSize(880, 600), 12, Panel);

                // -------------------------------------------------
                // Buttons
                // -------------------------------------------------
                FShokoRenderer::DrawRoundedRect(FLocation(140, 220), FSize(140, 40), 8, Accent);
                FShokoRenderer::DrawRoundedRect(FLocation(300, 220), FSize(140, 40), 8, PanelDark);
                FShokoRenderer::DrawRoundedRectBorder(FLocation(300, 220), FSize(140, 40), 8, Border, 1, EShokoRendererBorderType::Inside);

                // -------------------------------------------------
                // Toggles
                // -------------------------------------------------
                // Off
                FShokoRenderer::DrawRoundedRect(FLocation(140, 290), FSize(60, 28), 14, PanelDark);
                FShokoRenderer::DrawCircle(FLocation(154, 304), 10, Disabled);

                // On
                FShokoRenderer::DrawRoundedRect(FLocation(220, 290), FSize(60, 28), 14, Accent);
                FShokoRenderer::DrawCircle(FLocation(265, 304), 10, PanelDark);
        
                // -------------------------------------------------
                // Checkboxes
                // -------------------------------------------------
                FShokoRenderer::DrawRectBorder(FLocation(140, 340), FSize(24, 24), Border, 2, EShokoRendererBorderType::Inside);
                FShokoRenderer::DrawRect(FLocation(180, 340), FSize(24, 24), Accent);

                // -------------------------------------------------
                // List
                // -------------------------------------------------
                for(int16 i = 0; i < 4; ++i)
                {
                    int16 y = 390 + i * 50;
                    FShokoRenderer::DrawRoundedRect(FLocation(140, y), FSize(400, 36), 6, i == 2 ? PanelDark : Panel);
                    if (i == 2) FShokoRenderer::DrawRect(FLocation(140, y), FSize(4, 36), Accent);
                }

                // -------------------------------------------------
                // Progress bar
                // -------------------------------------------------
                FShokoRenderer::DrawRoundedRect(FLocation(140, 600), FSize(300, 14), 7, PanelDark);
                FShokoRenderer::DrawRoundedRect(FLocation(140, 600), FSize(180, 14), 7, Accent);

                // -------------------------------------------------
                // Decorative Bezier / Path (framework flex)
                // -------------------------------------------------
                FShokoRenderer::DrawQuadraticBezier(FLocation(600, 200), FLocation(750, 100), FLocation(900, 200), AccentSoft);

                FShokoRenderer::DrawPath<5>(
                    {
                        FLocation(600, 500),
                        FLocation(650, 530),
                        FLocation(700, 500),
                        FLocation(750, 530),
                        FLocation(800, 500)
                    },
                    Accent,
                    2
                );
            }
            FShokoRenderer::PostRender();
        }
    }
}
