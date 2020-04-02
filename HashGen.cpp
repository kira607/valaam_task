//
// Created by kirill on 27.03.2020.
//

#include "HashGen.h"

HashGen::HashGen(std::shared_ptr<FixedQueue<Unit>> _buff1, std::shared_ptr<FixedQueue<Unit>> _buff2, int _unit_size)
:buff1{std::move(_buff1)},buff2{std::move(_buff2)},unit(_unit_size)
{

}

void HashGen::run()
{
    unit = buff1->pop();
    unit.gen();
    buff2->push(unit);
}


