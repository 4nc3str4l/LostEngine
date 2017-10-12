#pragma once

namespace LostEngine { namespace InputHandlers { 

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

	class Input
	{
	public:
		static void Initialize();
		static bool IsKeyPressed(unsigned int keycode);
		static bool IsMouseButtonPressed(unsigned int button);
		static double MousePosX;
		static double MousePosY;
		static double ScrollOffset;
		static bool keys[];
		static bool mouseButtons[];
	};
}}