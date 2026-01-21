#pragma once

#include <string>

#include "Platform/PlatformWindow.h"

namespace Shoko
{
    class SWindow
    {
        
    public:
        SWindow() : PlatformWindow(FShokoPlatformWindow()) { PlatformWindow.Initialize(); }
        
        void Deinitialize() const
        {
            PlatformWindow.Deinitialize();
        }
        
        SWindow& SetTitle(const std::string& Title)
        {
            PlatformWindow.SetTitle(Title.c_str());
            return *this;
        }
        
        SWindow& SetSize(FUIntVector2D Size)
        {
            PlatformWindow.SetSize(Size);
            return *this;
        }
        
        constexpr void ActivateRenderContext() const
        {
            // TODO: Context Switcher
#if SHOKO_RENDERER == SHOKO_RENDERER_SDL2
            FShokoPlatformRenderer::SDLRenderer = PlatformWindow.SDLRenderer;
#endif
        }
        
    private:
        FShokoPlatformWindow PlatformWindow;
    };
}
