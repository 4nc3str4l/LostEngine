#include "Window.h"

void Window::process_input()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	
}

void framebuffer_size_callback(GLFWwindow* _window, int _width, int _height)
{
	Window* win = (Window*)_window;
	glViewport(0, 0, _width, _height);
	win->Width = _width;
	win->Height = _height;
}

Window::Window(int _width, int _heigth, char* _title)
{
	Width = _width;
	Height = _heigth;
	Title = _title;
}

Window::~Window()
{
	glfwTerminate();
}

int Window::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	
	glfwSetWindowUserPointer(window, this);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, Width, Height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(0);
}

bool Window::IsApplicationRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::Update()
{
	process_input();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::ClearColor(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a)
{
	glClearColor(_r, _g, _b, _a);
}
