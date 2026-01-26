#include "OpenGLPlatformWindow.h"

using namespace Shoko;

#include <iostream>

bool FShokoOpenGLPlatformWindow::Initialize()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW init failed\n";
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    Window = glfwCreateWindow(800, 600, "[GLFW] Window", nullptr, nullptr);
    if(!Window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);

    return true;
}

void FShokoOpenGLPlatformWindow::Deinitialize()
{
    if (Window)
    {
        glfwDestroyWindow(Window);
        Window = nullptr;
    }

    glfwTerminate();
}

void FShokoOpenGLPlatformWindow::SetTitle(const char* NewTitle) const
{
    glfwSetWindowTitle(Window, NewTitle);
}

void FShokoOpenGLPlatformWindow::SetSize(FSize Size) const
{
    glfwSetWindowSize(Window, Size.X, Size.Y);
}

/*
void FShokoOpenGLPlatformWindow::PollEvents() const
{
    glfwPollEvents();
}

bool FShokoOpenGLPlatformWindow::ShouldClose() const
{
    return glfwWindowShouldClose(Window);
}

void FShokoOpenGLPlatformWindow::SwapBuffers() const
{
    glfwSwapBuffers(Window);
}
*/
