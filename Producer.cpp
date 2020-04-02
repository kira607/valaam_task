//
// Created by kirill on 26.03.2020.
//

#include "Producer.h"


Producer::Producer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string& name_of_file, int _unit_size)
:buffer{std::move(_buffer)},fin(name_of_file),unit(_unit_size),unit_read{0}
{

}

bool Producer::run()
{
    if(test_mode) std::cout << unit_read << " UNIT::\n";
    unit.refill();
    if(unit.read(fin))
    {
        if(test_mode) ++unit_read;
        if(test_mode) std::cout << "Producer:: I read:\n" << unit << "\n";
        buffer->push(unit);
        return true;
    }
    else
    {
        //say that producer will no longer provide units
        if(test_mode) std::cout << "Producer:: I'm dead now, no units left\nI read " << unit_read << " units\n";
        return false;
    }
}