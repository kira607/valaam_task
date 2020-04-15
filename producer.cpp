//
// Created by kirill on 26.03.2020.
//

#include <thread>
#include "producer.h"

Producer::Producer(std::shared_ptr<FixedQueue<Unit>> buffer,
                   const std::string& name_of_in_file,
                   int unit_size)
: buffer_{std::move(buffer)},
  fin_(name_of_in_file, std::ios_base::binary | std::ios_base::in),
  unit_(unit_size)
{

}

void Producer::Run()
{
    unit_.Refill();
    unit_.Read(fin_);
    do
    {
        buffer_->Push(unit_);
        unit_.Refill();
    } while (unit_.Read(fin_));
    buffer_->Kill();
}