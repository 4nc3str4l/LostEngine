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

	void LEngine::HandleInput()
	{
		gameLogic->Input(window, timer->DeltaTime);
		Input::ScrollOffset = 0;
	}

	void LEngine::Run()
	{
		float elapsedTime;
		float acumulator = 0.0f;
		float interval = 1.0f / 60;

		while (window->IsOpen())
		{
			timer->Update();
			elapsedTime = timer->DeltaTime;
			acumulator += elapsedTime;

			HandleInput();

			while (acumulator >= interval)
			{
				Update(interval);
				acumulator -= interval;
			}
			Render();
		}
	}

	void LEngine::Update(float _delta)
	{
		gameLogic->Update(_delta, window);
	}

	void LEngine::Render()
	{
		window->Clear();
		gameLogic->Render(window);
		window->Update();
	}



	LEngine::~LEngine()
	{
		delete loader;
		delete window;
		delete gameLogic;
		delete timer;
	}
}

