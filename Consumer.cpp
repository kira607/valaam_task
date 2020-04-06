//
// Created by kirill on 27.03.2020.
//

#include "Consumer.h"

Consumer::Consumer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string &_name_of_file, int _unit_size)
:buffer{std::move(_buffer)},fout(_name_of_file),unit(_unit_size)
{

}

void Consumer::run()
{
    try
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
    catch(std::exception &ex)
    {
        std::cout << color::red << ex.what() << color::none;
    }
}
