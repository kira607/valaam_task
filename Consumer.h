//
// Created by kirill on 27.03.2020.
//

#ifndef UNTITLED_CONSUMER_H
#define UNTITLED_CONSUMER_H


#include "Unit.h"

class Consumer
{
private:
    Unit unit;
public:
    Consumer(std::vector<Unit> &buff, std::ofstream &fout);
};


#endif //UNTITLED_CONSUMER_H
