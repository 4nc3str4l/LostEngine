#pragma once
#include "../Gfx/Utils/Window.h"
#include "../Gfx/Utils/Loader.h"
#include "../Input/Input.h"

using namespace LostEngine;
using namespace Gfx;
using namespace InputHandlers;

namespace LostEngine { namespace Logic {
class GameLogic
{
public:
    virtual void Init(Window* _window, Loader* _loader) = 0;
    virtual void Update(float _delta, Window* _window) = 0;
    virtual void Render(Window* _window) = 0;
};
}}