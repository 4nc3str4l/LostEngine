#include "LostEngine.h"

namespace le {

	LEngine::LEngine(char* _windowTitle, bool _vSync, int _width, int _height, const std::string& base, GameLogic* _gameLogic)
	{
		window = new Window(_windowTitle, _width, _height, false);
		loader = new Loader(base);
		gameLogic = _gameLogic;
		timer = new Timer();
		FileSystem::basePath = base;
	}

	void LEngine::Start() 
	{
		LOG_SPECIAL("############################################");
		LOG_SPECIAL("            LOST ENGINE ", ENGINE_VERSION);
		LOG_SPECIAL("############################################");
		LOG_INFO("Init Input");
		Input::Initialize();
		LOG_CORRECT("Init Input Correct!");
		
		LOG_INFO("Init Graphics");
		window->Init();
		LOG_CORRECT("Init Graphics Correct!");
		
		LOG_INFO("Init Game Logic");
		gameLogic->Init(window, loader);
		LOG_CORRECT("Init Game Logic Correct!");

		Run();
	}

	void LEngine::HandleInput()
	{
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

			while (acumulator >= interval)
			{
				float realDelta = timer->DeltaTime;
				timer->DeltaTime = interval;
				Update(interval);
				acumulator -= interval;
				timer->DeltaTime = realDelta;
				HandleInput();
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

		LOG_CORRECT("Clean Complete!");
	}
}

