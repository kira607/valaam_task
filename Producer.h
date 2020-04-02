//
// Created by kirill on 26.03.2020.
//

#ifndef UNTITLED_PRODUCER_H
#define UNTITLED_PRODUCER_H

#include <memory>
#include <utility>
#include <mutex>

#include "Unit.h"
#include "FixedQueue.h"
#include "condit_vars.h"

class Producer
{
private:
    Unit unit;
    std::shared_ptr<FixedQueue<Unit>> buffer;
    std::ifstream fin;
    mutable std::mutex mut;
public:
    explicit Producer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string &_name_of_file, int _unit_size);
    void run();
};


#endif //UNTITLED_PRODUCER_H
