#include "LostEngine.h"

namespace LostEngine {

	LEngine::LEngine(char* _windowTitle, bool _vSync, int _width, int _height, GameLogic* _gameLogic)
	{
		window = new Window(_windowTitle, _width, _height, false);
		loader = new Loader();
		gameLogic = _gameLogic;
		timer = new Timer();
	}

	void LEngine::Start() 
	{
		Input::Initialize();
		window->Init();
		gameLogic->Init(window, loader);
		Run();
	}

	void LEngine::Run()
	{
		while (window->IsOpen())
		{
			window->Clear();

			timer->Update();
			gameLogic->Input(window, timer->DeltaTime);
			Input::ScrollOffset = 0;
			gameLogic->Update(timer->DeltaTime, window);
			
			window->Update();
		}
	}

	LEngine::~LEngine()
	{
		delete loader;
		delete window;
		delete gameLogic;
		delete timer;
	}
}

