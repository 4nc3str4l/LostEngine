#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace LostEngine { namespace Gfx {

class Window
{

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

public:
    Window(char* _title, int _width, int _heigth, bool _vSync);
    ~Window();
    int Init();
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
    double MousePosX;
    double MousePosY;
public:

    bool isKeyPressed(unsigned int keycode) const;
    bool isMouseButtonPressed(unsigned int button) const;

private:
    bool keys[MAX_KEYS];
    bool mouseButtons[MAX_BUTTONS];

    friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

}}