//
// Created by kirill on 26.03.2020.
//

#include <thread>
#include "Producer.h"

Producer::Producer(std::shared_ptr<FixedQueue<Unit>> _buffer,
                   const std::string& _name_of_file,
                   int _unit_size)
:buffer{std::move(_buffer)},fin(_name_of_file,std::ios_base::binary|std::ios_base::in),unit(_unit_size)
{

}

void Producer::run()
{
    unit.refill();
    unit.read(fin);
    do
    {
        buffer->push(unit);
        unit.refill();
    } while (unit.read(fin));
    buffer->kill();
}