#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace LostEngine { namespace Gfx {

class Window
{
public:
    Window(char* _title, int _width, int _heigth, bool _vSync);
    ~Window();
    int Init();
    void RestoreState();
    void Update();
    bool IsOpen();
    void SetTitle(const char* _title);
public:
    const char* Title;
    int Width;
    int Heigth;
    GLFWwindow* WindowHandle;
    bool Resized;
    bool VSync;
};

}}