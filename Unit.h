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

    void init(unsigned int unit_size_in);
public:
    explicit Unit(int unit_size_in = 0);
    explicit Unit(char *unit_size_str);
    ~Unit();

    [[nodiscard]] int size() const;
    [[nodiscard]] size_t hash() const;
    [[nodiscard]] std::basic_string<char> data() const;

    void resize(int to_resize);
    void fill();
    void gen();
    size_t read(std::ifstream &file);
    void write(std::ofstream &file);
    void disp();
    void info();
};

#endif //UNTITLED_UNIT_H
