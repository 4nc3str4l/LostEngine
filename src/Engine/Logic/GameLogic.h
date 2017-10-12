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
    // TODO (@4nc3stral) we need the input here.
    virtual void Init(Window* _window, Loader* _loader) = 0;
    // TODO (@4nc3str4l) we need mouse input
    virtual void Input(Window* _window, float _delta) = 0;
    // TODO (@4nc3str4l) we need the mouse input here.
    virtual void Update(float _delta, Window* _window) = 0;
    virtual void Render(Window* _window) = 0;
};
}}