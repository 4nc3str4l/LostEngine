#pragma once
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <iostream>
#include "../../Input/Input.h"

namespace le { namespace gfx {
using namespace input;

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
    static int Width;
    static int Heigth;
	sf::Window* WindowHandle;
    bool Resized;
    bool VSync;
private:
	bool shoudClose = false;
    void logGPUInfo();
};

}}