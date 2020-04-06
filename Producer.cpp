//
// Created by kirill on 26.03.2020.
//

#include "Producer.h"


Producer::Producer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string& name_of_file, int _unit_size)
:buffer{std::move(_buffer)},fin(name_of_file),unit(_unit_size),unit_read{0}
{

}

void Producer::run()
{
    std::cout << unit_read << " UNIT::\n";

    unit.refill();
    unit.read(fin);
    do
    {
        ++unit_read;
        std::cout << color::red << "Producer::(" << unit_read << ") I read:\n" << color::none << unit << "\n";

        buffer->push(unit);
        unit.refill();
        std::cout << color::blue << "buffer dead:" << buffer->dead() << color::none << "\n";
    }
    while(unit.read(fin));

    buffer->kill();
    //say that producer will no longer provide units
    std::cout << "Producer:: I'm dead now, no units left\nI read " << unit_read << " units\n";
}