#pragma once

#include <string>

#include SHOKO_PLATFORM_WINDOW_INCLUDE

namespace Shoko
{
    class SWindow
    {
        
    public:
        SWindow() : PlatformWindow(FShokoPlatformWindow()) { PlatformWindow.Initialize(); }
        
        void Deinitialize()
        {
            PlatformWindow.Deinitialize();
        }
        
        SWindow& SetTitle(const std::string& Title)
        {
            PlatformWindow.SetTitle(Title.c_str());
            return *this;
        }
        
        SWindow& SetSize(FSize Size)
        {
            PlatformWindow.SetSize(Size);
            FShokoOpenGLPlatformRenderer::WindowWidth  = Size.X;
            FShokoOpenGLPlatformRenderer::WindowHeight = Size.Y;
            return *this;
        }
        
        constexpr void ActivateRenderContext() const
        {
            // TODO: Context Switcher
            FShokoPlatformInput::Window = PlatformWindow.Window;
            FShokoPlatformRenderer::Window = PlatformWindow.Window;
            
/*#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2
            FShokoPlatformRenderer::SDLRenderer = PlatformWindow.SDLRenderer;
#endif*/
        }
        
    private:
        FShokoPlatformWindow PlatformWindow;
    };
}
