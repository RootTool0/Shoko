#pragma once

#include <string>

#include "Platform/PlatformWindow.h"
#include "Platform/PlatformRenderer.h"

namespace Shoko
{
    class SWindow
    {
    public:
        SWindow() { Initialize(); }
        
        void Initialize()
        {
            PlatformWindow = FShokoPlatformWindow();
            PlatformWindow.Initialize();
        }
        
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
            FShokoPlatformRenderer::SDLRenderer = PlatformWindow.SDLRenderer;
        }
        
    private:
        FShokoPlatformWindow PlatformWindow;
    };
}
