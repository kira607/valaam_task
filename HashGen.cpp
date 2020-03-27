//
// Created by kirill on 27.03.2020.
//

#include "HashGen.h"

HashGen::HashGen(std::vector<Unit> &buff1, std::vector<Unit> &buff2)
{
    unit = buff1.front();
    buff1.erase(buff1.begin());
    unit.gen();
    buff2.push_back(unit);
}
