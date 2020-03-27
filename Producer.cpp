//
// Created by kirill on 26.03.2020.
//

#include "Producer.h"

Producer::Producer(std::vector<Unit> &buffer, std::ifstream &fin)
{
    unit.fill();
    unit.read(fin);
    buffer.push_back(unit);
}
