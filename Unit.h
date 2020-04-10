//
// Created by kirill on 20.03.2020.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H

#include <fstream>
#include <string>
#include <utility> //move

class Unit
{
private:
    std::basic_string<char> unit;
    int unit_size;
    size_t unit_hash;
public:
    explicit Unit(int unit_size_in = 0);
    ~Unit() = default;

    void refill();
    void setHash(size_t _hash);
    std::basic_string<char> data();
    size_t read(std::ifstream &file);
    void write(std::ofstream &file);

    friend std::ostream& operator<<(std::ostream& out, const Unit& unit);
};

#endif //UNTITLED_UNIT_H
