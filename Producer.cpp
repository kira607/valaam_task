//
// Created by kirill on 26.03.2020.
//

#include "Producer.h"


Producer::Producer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string& name_of_file, int _unit_size)
:buffer{std::move(_buffer)},fin(name_of_file),unit(_unit_size)
{

}

void Producer::run()
{
    unit.refill();
    if(unit.read(fin))
    {
        buffer->push(unit);
    }
    else
    {
        //say that producer will no longer provide units
        std::cout << "Producer:: I'm dead now, no units left\n";
    }
}
