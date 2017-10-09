#pragma once

namespace LostEngine { namespace Logic {
class GameLogic
{
public:
    // TODO (@4nc3stral) we need a window and input here.
    virtual void Init() = 0;
    // TODO (@4nc3str4l) we need window and mouse input
    virtual void Input() = 0;
    // TODO (@4nc3str4l) we need the mouse input and the window here.
    virtual void Update(float _delta) = 0;
    // TODO (@4nc3str4l) we need the window here
    virtual void Render() = 0;
};
}}