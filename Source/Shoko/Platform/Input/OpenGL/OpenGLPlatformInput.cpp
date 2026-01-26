#include "OpenGLPlatformInput.h"

#include <GLFW/glfw3.h>

#include "Types/InputEvent.h"

using namespace Shoko;

GLFWwindow* FShokoOpenGLPlatformInput::Window = nullptr;
uint8 FShokoOpenGLPlatformInput::Key = 0;
bool FShokoOpenGLPlatformInput::PrevKeyState[GLFW_KEY_LAST + 1] = {};

bool FShokoOpenGLPlatformInput::Initialize() { return true; }
void FShokoOpenGLPlatformInput::Deinitialize()
{
    Window = nullptr;
}
void FShokoOpenGLPlatformInput::PullEvents()
{
    if (glfwWindowShouldClose(Window))
    {
        Key = FInputEvent::GetKey(ESystemKey::Window_Close);
        return;
    }
    
    for (int k = GLFW_KEY_SPACE; k <= GLFW_KEY_LAST; ++k)
    {
        int state = glfwGetKey(Window, k);
        bool isDown = state == GLFW_PRESS;
        bool wasDown = PrevKeyState[k];

        if (isDown && !wasDown)
        {
            if (GLFW_KEY_A <= k && k <= GLFW_KEY_Z)
                Key = FInputEvent::GetKey(static_cast<EKeyboardKey>(k));
            else if (GLFW_KEY_0 <= k && k <= GLFW_KEY_9)
                Key = FInputEvent::GetKey(static_cast<EKeyboardKey>(k));
            else if (k == GLFW_KEY_BACKSPACE)
                Key = FInputEvent::GetKey(EKeyboardKey::Special_Backspace);
            else if (k == GLFW_KEY_SPACE)
                Key = FInputEvent::GetKey(EKeyboardKey::Special_Space);
            else if (k == GLFW_KEY_PERIOD)
                Key = FInputEvent::GetKey(EKeyboardKey::Special_Period);
            else if (k == GLFW_KEY_COMMA)
                Key = FInputEvent::GetKey(EKeyboardKey::Special_Comma);
            else if (k == GLFW_KEY_SEMICOLON)
                Key = FInputEvent::GetKey(EKeyboardKey::Special_Semicolon);
            else
                Key = 0;

            PrevKeyState[k] = true;
            return;
        }

        PrevKeyState[k] = isDown;
    }

    Key = 0;
    
    glfwPollEvents();
}

uint8 FShokoOpenGLPlatformInput::GetKey() { return Key; }

bool FShokoOpenGLPlatformInput::GetLeftShift()  { return glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetRightShift() { return glfwGetKey(Window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetLeftAlt()    { return glfwGetKey(Window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetRightAlt()   { return glfwGetKey(Window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetLeftCtrl()   { return glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetRightCtrl()  { return glfwGetKey(Window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetLeftCmd()    { return glfwGetKey(Window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetRightCmd()   { return glfwGetKey(Window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS; }

FLocation FShokoOpenGLPlatformInput::GetMousePosition()
{
    double x, y;
    glfwGetCursorPos(Window, &x, &y);
    return FLocation(static_cast<int16>(x), static_cast<int16>(y));
}
bool FShokoOpenGLPlatformInput::GetMouseLeftButton()   { return glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetMouseRightButton()  { return glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS; }
bool FShokoOpenGLPlatformInput::GetMouseMiddleButton() { return glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS; }
