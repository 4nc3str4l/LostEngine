#pragma once

#include "Gfx/Utils/Window.h"
#include "Logic/GameLogic.h"
#include "Gfx/Utils/Loader.h"
#include "Tools/Timer.h"

using namespace Logic;
using namespace Gfx;
using namespace Tools;

namespace LostEngine {
	class LEngine
	{
	public:
		LEngine(char* _windowTitle, bool _vSync, int _width, int _height, GameLogic* _gameLogic);
		~LEngine();
		void Start();
		void Run();
	private:
		Window* window;
		GameLogic* gameLogic;
		Loader* loader;
		Timer* timer;
	};



}