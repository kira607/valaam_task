//
// Created by kirill on 27.03.2020.
//

#include "hash_generator.h"

HashGenerator::HashGenerator(std::shared_ptr<FixedQueue<Unit>> buffer1, std::shared_ptr<FixedQueue<Unit>> buffer2, int unit_size)
: buffer1_{std::move(buffer1)}, buffer2_{std::move(buffer2)}, unit_(unit_size)
{

}

void HashGenerator::Run()
{
    while (true)
    {
        if (buffer1_->Empty() && buffer1_->Dead())
        {
            buffer2_->Kill();
            break;
        }
        else
        {
            unit_ = buffer1_->Pop();
            unit_.set_hash(GenerateHash(unit_));
            buffer2_->Push(unit_);
        }
    }

}

size_t HashGenerator::GenerateHash(Unit &unit)
{
    if(!unit.Data().empty())
        return hash_generator_(unit.Data());
    else
        return 0;
}