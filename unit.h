//
// Created by kirill on 20.03.2020.
//

#ifndef SIGNATURE_UNIT_H
#define SIGNATURE_UNIT_H

#include <fstream>
#include <string>
#include <utility> //move

class Unit
{
public:
    explicit Unit(int unit_size = 0);
    ~Unit() = default;

    void Refill();
    void set_hash(size_t hash);
    std::basic_string<char> Data();
    size_t Read(std::ifstream &file);
    void Write(std::ofstream &file);

    friend std::ostream& operator<<(std::ostream& out, const Unit& unit);
private:
    std::basic_string<char> unit_;
    int unit_size_;
    size_t hash_;
};

#endif //SIGNATURE_UNIT_H
