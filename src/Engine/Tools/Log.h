#pragma once

#include <iostream>
#include <string>
#ifdef WIN32
#include <windows.h>
#endif

namespace LostEngine { namespace Tools {

#define ENGINE_SPECIAL_COLOR 14
#define ENGINE_INFO_COLOR 9
#define ENGINE_REGULAR_COLOR 15
#define ENGINE_ERROR_COLOR 12
#define ENGINE_CORRECT_COLOR 2

template <typename T>
static void SPECIAL(T t)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_SPECIAL_COLOR);
#endif
	std::cout << t;
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
}

template <typename T, typename... Args>
static void SPECIAL(T t, Args... _specialMessage)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_SPECIAL_COLOR);
#endif
	std::cout << t;
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	SPECIAL(_specialMessage...);
}

template <typename T>
static void INFO(T t)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_INFO_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
}

template <typename T, typename... Args>
static void INFO(T t, Args... _infoMessage)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_INFO_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	INFO(_infoMessage...);
}

template <typename T>
static void FAIL(T t)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_ERROR_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
}

template <typename T, typename... Args>
static void FAIL(T t, Args... _errorText)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_ERROR_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	FAIL(_errorText...);
}

template <typename T>
static void CORRECT(T t)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_CORRECT_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
}

template <typename T, typename... Args>
static void CORRECT(T t, Args... _correctText)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_CORRECT_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	CORRECT(_correctText...);
}

template <typename T>
static void MESSAGE(T t)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
	MESSAGE(_message...);
}

template <typename T, typename... Args>
static void MESSAGE(T t, Args... _message)
{
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	std::cout << "LOST ENGINE >> \t" << t << " ";
	MESSAGE(_message...);
}

#define LOG_SPECIAL(...) SPECIAL(__VA_ARGS__); std::cout << "\n"
#define LOG_INFO(...) INFO(__VA_ARGS__); std::cout << "\n"
#define LOG_FAIL(...) FAIL(__VA_ARGS__); std::cout << "\n"
#define LOG_CORRECT(...) CORRECT(__VA_ARGS__); std::cout << "\n"
#define LOG_MESSAGE(...) MESSAGE(__VA_ARGS__); std::cout << "\n"

}}