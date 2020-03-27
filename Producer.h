//
// Created by kirill on 26.03.2020.
//

#ifndef UNTITLED_PRODUCER_H
#define UNTITLED_PRODUCER_H

#include "Unit.h"

class Producer
{
private:
    Unit unit;
    std::vector<Unit> &buffer;
    std::ifstream &fin;
public:
    Producer(std::vector<Unit> &_buffer, std::ifstream &_fin):;
};


#endif //UNTITLED_PRODUCER_H
