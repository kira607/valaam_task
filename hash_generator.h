//
// Created by kirill on 27.03.2020.
//

#ifndef SIGNATURE_HASH_GENERATOR_H
#define SIGNATURE_HASH_GENERATOR_H

#include <memory>
#include <utility>

#include "unit.h"
#include "fixed_queue.h"
#include "color.h"

class HashGenerator
{
public:
    HashGenerator(std::shared_ptr<FixedQueue<Unit>> buffer1, std::shared_ptr<FixedQueue<Unit>> buffer2, int unit_size);
    void Run();
private:
    size_t GenerateHash(Unit& unit);
    std::shared_ptr<FixedQueue<Unit>> buffer1_;
    std::shared_ptr<FixedQueue<Unit>> buffer2_;
    std::hash<std::basic_string<char>> hash_generator_;
    Unit unit_;
};


#endif //SIGNATURE_HASH_GENERATOR_H
