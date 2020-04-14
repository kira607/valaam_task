//
// Created by kirill on 27.03.2020.
//

#include <thread>
#include "Consumer.h"

Consumer::Consumer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string &_name_of_file, int _unit_size)
:buffer{std::move(_buffer)},fout(_name_of_file,std::ios_base::binary|std::ios_base::trunc),unit(_unit_size)
{

}

void Consumer::run()
{
    while (true)
    {
        unit = buffer->pop();
        unit.write(fout);
        if (buffer->empty() && buffer->dead())
        {
            break;
        }
    }
}
