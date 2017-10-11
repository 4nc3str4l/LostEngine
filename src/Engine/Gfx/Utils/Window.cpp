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

    for (int i = 0; i < MAX_KEYS; i++)
    {
        keys[i] = false;
    }

    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        mouseButtons[i] = false;
    }

    MousePosX = _width / 2.0f;
    MousePosY = _heigth / 2.0f;
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
    glfwSetKeyCallback(WindowHandle, key_callback);
    glfwSetMouseButtonCallback(WindowHandle, mouse_button_callback);
    glfwSetCursorPosCallback(WindowHandle, cursor_position_callback);
    glfwSetScrollCallback(WindowHandle, scroll_callback);
    return 0;
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->mouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->MousePosX = xpos;
    win->MousePosY = ypos;
}

bool Window::isKeyPressed(unsigned int keycode) const
{
    if (keycode >= MAX_KEYS)
        return false;

    return keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const
{
    if (button >= MAX_BUTTONS)
        return false;

    return mouseButtons[button];
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->scrollOffset = yoffset;
}

}}