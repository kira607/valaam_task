//
// Created by kirill on 26.03.2020.
//

#include "Producer.h"


Producer::Producer(std::shared_ptr<FixedQueue<Unit>> _buffer,
                   const std::string& _name_of_file,
                   int _unit_size)
:buffer{std::move(_buffer)},fin(_name_of_file),unit(_unit_size)
{

}

void Producer::run()
{
    try
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
    catch(std::exception &ex)
    {
        std::cout << color::red << ex.what() << color::none;
    }
}