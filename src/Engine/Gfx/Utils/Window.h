#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Input/Input.h"

namespace Lost { namespace Gfx {
using namespace InputHandlers;

class Window
{
public:
    Window(char* _title, int _width, int _heigth, bool _vSync);
    ~Window();
    int Init();
    void Update();
    bool IsOpen();
    void SetTitle(const char* _title);
	void Clear();
	void Close();
public:
    const char* Title;
    int Width;
    int Heigth;
    GLFWwindow* WindowHandle;
    bool Resized;
    bool VSync;
private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void logGPUInfo();
};

}}