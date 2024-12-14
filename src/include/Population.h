#pragma once

#include "Entity.h"
#include <cstdint>
#include <vector>

class Population
{
private:
    const double _r;
    const double _w;
    uint32_t _k;
    uint32_t _p;
    std::vector<Entity> _ppltn;

public:
    Population(/* args */);
    ~Population();
};
