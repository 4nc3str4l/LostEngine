#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

class Window
{
public:
	GLFWwindow* window;
	int Width;
	int Height;
	char* Title;
public:
	Window(int _width, int _heigth, char* _title);
	~Window();
	int Init();
	bool IsApplicationRunning();
	void Update();
	void ClearColor(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a);
private:
	void Window::process_input();
};

