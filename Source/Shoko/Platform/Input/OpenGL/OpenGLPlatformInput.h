#pragma once

#include <GLFW/glfw3.h>

#include "Types/Vector2D.h"

namespace Shoko
{
    class FShokoOpenGLPlatformInput
    {
#include "../InputDeclaration.h"
        
    public:
        static GLFWwindow* Window;
        
    private:
        static uint8 Key;
        static bool PrevKeyState[GLFW_KEY_LAST + 1];
    };
    
    using FShokoPlatformInput = FShokoOpenGLPlatformInput;
}
