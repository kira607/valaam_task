//
// Created by kirill on 27.03.2020.
//

#ifndef UNTITLED_HASHGEN_H
#define UNTITLED_HASHGEN_H

#include <memory>
#include <utility>
#include <mutex>

#include "Unit.h"
#include "FixedQueue.h"

class HashGen
{
private:
    std::shared_ptr<FixedQueue<Unit>> buff1;
    std::shared_ptr<FixedQueue<Unit>> buff2;
    std::hash<std::basic_string<char>> hash_gen; //if(!unit.empty())

    Unit unit;
    std::mutex mut;
public:
    HashGen(std::shared_ptr<FixedQueue<Unit>> _buff1, std::shared_ptr<FixedQueue<Unit>> _buff2, int _unit_size);
    void run();
    size_t gen_hash(Unit& _unit);
};


#endif //UNTITLED_HASHGEN_H
