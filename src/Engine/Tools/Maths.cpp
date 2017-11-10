#include "Maths.h"

#include<iostream>

namespace LostEngine { namespace Tools { 

float Maths::GetRandomFloat(float _minimum, float _maximum)
{   
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = _maximum - _minimum;
    float r = random * diff;
    return _minimum + r;
}

}}