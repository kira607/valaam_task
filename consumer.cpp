//
// Created by kirill on 27.03.2020.
//

#include "consumer.h"

Consumer::Consumer(std::shared_ptr<FixedQueue<Unit>> buffer, const std::string &name_of_out_file, int unit_size)
: buffer_{std::move(buffer)},
  file_out_{name_of_out_file, std::ios_base::binary | std::ios_base::trunc},
  unit_{unit_size}
{

}

void Consumer::Run()
{
    while (true)
    {
        unit_ = buffer_->Pop();
        unit_.Write(file_out_);
        if (buffer_->Empty() && buffer_->Dead())
        {
            break;
        }
    }
}
