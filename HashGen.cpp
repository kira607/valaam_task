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
    try
    {
        while (true)
        {
            unit = buff1->pop();
            unit.setHash(gen_hash(unit));
            buff2->push(unit);

            if (buff1->empty() && buff1->dead())
            {
                buff2->kill();
                break;
            }
        }
    }
    catch(std::exception &ex)
    {
        std::cout << color::red << ex.what() << color::none;
    }
}

size_t HashGen::gen_hash(Unit &_unit)
{
    if(!_unit.data().empty())
        return hash_gen(_unit.data());
    else
        return 0;
}