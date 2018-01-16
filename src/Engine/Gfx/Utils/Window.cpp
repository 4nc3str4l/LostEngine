#include "Window.h"
#include "../../Tools/Log.h"
namespace LostEngine { namespace Gfx {
using namespace Tools;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window* ownWindow = (Window*)glfwGetWindowUserPointer(window);
    ownWindow->Width = width;
    ownWindow->Heigth = height;
	LOG_INFO(ownWindow->Width, ", ",  ownWindow->Heigth);
	ownWindow->Resized = true;
	glViewport(0, 0, width, height);
}

Window::Window(char* _title, int _width, int _heigth, bool _vSync)
{
    Title = _title;
    Width = _width;
    Heigth = _heigth;
    VSync = _vSync;

    Input::MousePosX = _width / 2.0f;
	Input::MousePosY = _heigth / 2.0f;
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

    logGPUInfo();

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
	Resized = false;
    glfwSwapBuffers(WindowHandle);
    glfwPollEvents();
	//LOG_INFO(Input::MousePosX, ", ", Input::MousePosY);
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

void Window::Clear()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Close()
{
	glfwSetWindowShouldClose(WindowHandle, GLFW_TRUE);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::logGPUInfo()
{
    std::cout << "OpenGL version supported by this platform:\t" << glGetString(GL_VERSION) << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    Input::keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Window* win = (Window*) glfwGetWindowUserPointer(window);
    Input::mouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Input::MousePosX = xpos;
    Input::MousePosY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Input::ScrollOffset = yoffset;
}

}}