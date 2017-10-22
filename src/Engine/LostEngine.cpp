#include "LostEngine.h"

namespace LostEngine {

	LEngine::LEngine(char* _windowTitle, bool _vSync, int _width, int _height, const std::string& base, GameLogic* _gameLogic)
	{
		window = new Window(_windowTitle, _width, _height, false);
		loader = new Loader(base);
		gameLogic = _gameLogic;
		timer = new Timer();
	}

	void LEngine::Start() 
	{

		LOG::SPECIAL("############################################");
		LOG::SPECIAL("            LOST ENGINE V.0.1a");
		LOG::SPECIAL("############################################");
		
		LOG::INFO("Init Input");
		Input::Initialize();
		LOG::CORRECT("Init Input Correct!");
		
		LOG::INFO("Init Graphics");
		window->Init();
		LOG::CORRECT("Init Graphics Correct!");
		
		LOG::INFO("Init Game Logic");
		gameLogic->Init(window, loader);
		LOG::CORRECT("Init Game Logic Correct!");

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

			HandleInput();

			while (acumulator >= interval)
			{
				float realDelta = timer->DeltaTime;
				timer->DeltaTime = interval;
				Update(interval);
				acumulator -= interval;
				timer->DeltaTime = realDelta;
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

		LOG::CORRECT("Clean Complete!");
	}
}

