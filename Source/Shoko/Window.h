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
        // ~SWindow() { PlatformWindow.Deinitialize(); }

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
            // Title = std::move(InTitle);
            return *this;
        }
        
        SWindow& SetSize(FUIntVector2D Size)
        {
            PlatformWindow.SetSize(Size);
            // Size = InSize;
            return *this;
        }

        constexpr void ActivateRenderContext() const
        {
            FShokoPlatformRenderer::SDLRenderer = PlatformWindow.SDLRenderer;
        }
        
    private:
        // FUIntVector2D Size = FUIntVector2D(800, 600);
        // std::string Title = "SWindow";
        
        FShokoPlatformWindow PlatformWindow;
    };
}

/*
Source\main.cpp
Source\Shoko\Config.h
Source\Shoko\Renderer.h
Source\Shoko\Shoko.h
Source\Shoko\Widgets.h
Source\Shoko\Window.h
Source\Shoko\Core\Aliases.h
Source\Shoko\Core\Macros.h
Source\Shoko\Core\Meta.h
Source\Shoko\Core\New.h
Source\Shoko\Platform\PlatformRenderer.h
Source\Shoko\Platform\PlatformWindow.h
Source\Shoko\Platform\Renderer\OpenGL\OpenGLPlatformRenderer.cpp
Source\Shoko\Platform\Renderer\OpenGL\OpenGLPlatformRenderer.h
Source\Shoko\Platform\Renderer\OpenGL\Shaders\Rect.frag
Source\Shoko\Platform\Renderer\OpenGL\Shaders\Rect.vert
Source\Shoko\Platform\Renderer\SDL2\SDL2PlatformRenderer.cpp
Source\Shoko\Platform\Renderer\SDL2\SDL2PlatformRenderer.h
Source\Shoko\Platform\Window\OpenGL\OpenGLPlatformWindow.cpp
Source\Shoko\Platform\Window\OpenGL\OpenGLPlatformWindow.h
Source\Shoko\Platform\Window\SDL2\SDL2PlatformWindow.cpp
Source\Shoko\Platform\Window\SDL2\SDL2PlatformWindow.h
Source\Shoko\Types\Color.h
Source\Shoko\Types\Geometry.h
Source\Shoko\Types\StaticArray.h
Source\Shoko\Types\Vector2D.h
Source\Shoko\Widgets\Border.h
Source\Shoko\Widgets\BoxWidget.h
Source\Shoko\Widgets\Button.h
Source\Shoko\Widgets\OpenGLContext.h
Source\Shoko\Widgets\Widget.h
Source\Shoko\Widgets\WidgetBase.h
Source\Shoko\Widgets\WidgetContainer.h
Source\Shoko\Widgets\WidgetWrapper.h
*/
