//
// Created by kirill on 20.03.2020.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  //convert
#include <cstring>  //strcmp
#include <functional> //hash
#include <utility> //move

#include "test_mode.h"
#include "color.h"

class Unit
{
private:
    std::basic_string<char> unit;
    int unit_size;
    std::hash<std::basic_string<char>> hash_gen;
    size_t unit_hash;
public:
    explicit Unit(int unit_size_in = 0);
    ~Unit();

    void refill();
    void gen();

    size_t read(std::ifstream &file);
    void write(std::ofstream &file);

    friend std::ostream& operator<<(std::ostream& out, const Unit& unit);
};

#endif //UNTITLED_UNIT_H
