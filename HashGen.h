//
// Created by kirill on 27.03.2020.
//

#ifndef UNTITLED_HASHGEN_H
#define UNTITLED_HASHGEN_H


#include "Producer.h"
#include "Consumer.h"

class HashGen
{
private:
    Unit unit;
public:
    HashGen(std::vector<Unit> &buff1, std::vector<Unit> &buff2);
};


#endif //UNTITLED_HASHGEN_H
