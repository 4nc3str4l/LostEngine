#include "Window.h"
#include "../../Tools/Log.h"
#include <string>

namespace le { namespace gfx {
using namespace tools;

int Window::Width = 0;
int Window::Heigth = 0;


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
	sf::ContextSettings settings(24, 8, 4, 3, 3);
	WindowHandle = new sf::Window(sf::VideoMode(Width, Heigth), Title, sf::Style::Default, settings);
	

	if (!gladLoadGL()) {
		LOG_FAIL("Could not load glad!");
		return -1;
	}

	WindowHandle->setActive(true);
	WindowHandle->setVerticalSyncEnabled(VSync ? 1 : 0);

	WindowHandle->setMouseCursorVisible(false);
	WindowHandle->setMouseCursorGrabbed(true);
    logGPUInfo();

    glEnable(GL_DEPTH_TEST);
    return 0;
}

void Window::Update()
{
	Resized = false;
	sf::Event event;
	while (WindowHandle->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			shoudClose = true;
		}
		else if (event.type == sf::Event::Resized)
		{
			// adjust the viewport when the window is resized
			glViewport(0, 0, event.size.width, event.size.height);
			Width = event.size.width; 
			Heigth = event.size.height;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			Input::keys[event.key.code] = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			Input::keys[event.key.code] = false;
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			Input::mouseButtons[event.mouseButton.button] = true;
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			Input::mouseButtons[event.mouseButton.button] = false;
		}
		if (event.type == sf::Event::MouseMoved)
		{
			Input::MousePosX = event.mouseMove.x;
			Input::MousePosY = event.mouseMove.y;
		}

	}

	if (Input::IsKeyPressed(sf::Keyboard::Escape))
	{
		shoudClose = true;
	}

	WindowHandle->display();
}

bool Window::IsOpen()
{
	return !shoudClose;
}

void Window::SetTitle(const char * _title)
{
    Title = _title;
	WindowHandle->setTitle(std::string(_title));
}

void Window::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Close()
{
}

Window::~Window()
{
	delete WindowHandle;
}

void Window::logGPUInfo()
{
    std::cout << "OpenGL version supported by this platform:\t" << glGetString(GL_VERSION) << std::endl;
}
}}