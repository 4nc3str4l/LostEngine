#pragma once

#include "Gfx/Utils/Window.h"
#include "Logic/GameLogic.h"
#include "Gfx/Utils/Loader.h"
#include "Tools/Timer.h"
#include "Tools/Log.h"
#include "Tools/FileSystem.h"
#include <string>

using namespace logic;
using namespace gfx;
using namespace tools;

namespace le {

const std::string ENGINE_VERSION = "V.0.2a";

class LEngine
{
public:
	LEngine(char* _windowTitle, bool _vSync, int _width, int _height, const std::string& base, GameLogic* _gameLogic);
	~LEngine();
	void Start();
	void Run();
	void Update(float _delta);
	void Render();
	void HandleInput();
private:
	Window* window;
	GameLogic* gameLogic;
	Loader* loader;
	Timer* timer;

};
}
