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

class LOG {
public:
	static void LOG::SPECIAL(const std::string& _specialMessage)
	{
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_SPECIAL_COLOR);
#endif
		std::cout << _specialMessage << "\n";
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	}

	static void LOG::INFO(const std::string& _infoMessage)
	{
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_INFO_COLOR);
#endif
		std::cout << "LOST ENGINE >> \t" << _infoMessage << "\n";
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
	}

	static void LOG::FAIL(const std::string& _errorText)
	{
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_ERROR_COLOR);
#endif
		std::cout << "LOST ENGINE >> \t" << _errorText << "\n";
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif

	}

	static void LOG::CORRECT(const std::string& _correctText)
	{
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_CORRECT_COLOR);
#endif
		std::cout << "LOST ENGINE >> \t" << _correctText << "\n";
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif

	}

	static void LOG::MESSAGE(const std::string& _message)
	{
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ENGINE_REGULAR_COLOR);
#endif
		std::cout << "LOST ENGINE >> \t" << _message << "\n";
	}
};

}}