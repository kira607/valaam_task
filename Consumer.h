//
// Created by kirill on 27.03.2020.
//

#ifndef UNTITLED_CONSUMER_H
#define UNTITLED_CONSUMER_H

#include <memory>
#include <utility>
#include <mutex>

#include "Unit.h"
#include "FixedQueue.h"
#include "condit_vars.h"

class Consumer
{
private:
    Unit unit;
    std::shared_ptr<FixedQueue<Unit>> buffer;
    std::ofstream fout;
    mutable std::mutex mut;
public:
    explicit Consumer(std::shared_ptr<FixedQueue<Unit>> _buffer, const std::string &_name_of_file, int _unit_size);
    void run();
};


#endif //UNTITLED_CONSUMER_H
