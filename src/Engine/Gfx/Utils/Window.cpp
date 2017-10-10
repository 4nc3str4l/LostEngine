#include "Window.h"

namespace LostEngine { namespace Gfx {

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* ownWindow = (Window*)glfwGetWindowUserPointer(window);
    ownWindow->Width = width;
    ownWindow->Heigth = height;
    std::cout << ownWindow->Width << ", " << ownWindow->Heigth << std::endl;
    glViewport(0, 0, width, height);
}

Window::Window(char* _title, int _width, int _heigth, bool _vSync)
{
    Title = _title;
    Width = _width;
    Heigth = _heigth;
    VSync = _vSync;
}

int Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    WindowHandle = glfwCreateWindow(Width, Heigth, Title, NULL, NULL);
    if (WindowHandle == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(WindowHandle);
    glfwSetInputMode(WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(VSync ? 1 : 0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetWindowUserPointer(WindowHandle, this);
    glfwSetFramebufferSizeCallback(WindowHandle, framebuffer_size_callback);
    return 0;
}

void Window::RestoreState()
{
}

void Window::Update()
{
    glfwSwapBuffers(WindowHandle);
    glfwPollEvents();
}

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(WindowHandle);
}

void Window::SetTitle(const char * _title)
{
    Title = _title;
    glfwSetWindowTitle(WindowHandle, Title);
}

Window::~Window()
{
    glfwTerminate();
}

}}