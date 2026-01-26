#pragma once

#include "Types/Vector2D.h"

#include <GLFW/glfw3.h>

namespace Shoko
{
    class FShokoOpenGLPlatformWindow
    {
#include "../WindowDeclaration.h"
        
    public:
        GLFWwindow* Window = nullptr;
    };

    using FShokoPlatformWindow = FShokoOpenGLPlatformWindow;
}
