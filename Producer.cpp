//
// Created by kirill on 26.03.2020.
//

#include "Producer.h"

Producer::Producer(std::vector<Unit> &_buffer, std::ifstream &_fin)
{
    unit.fill();
    unit.read(_fin);
    _buffer.push_back(unit);
}
