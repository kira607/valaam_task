//
// Created by kirill on 20.03.2020.
//

#include "unit.h"

Unit::Unit(int unit_size): unit_size_{unit_size}, hash_{0}
{
    if(unit_size >= 0)
    {
    unit_.resize(unit_size, 0);
    }
}

void Unit::Refill()
{
    for(auto &element:unit_)
    {
        element = 0;
    }
}

void Unit::set_hash(size_t hash)
{
    hash_ = hash;
}

size_t Unit::Read(std::ifstream &file)
{
    if(!unit_.empty() && unit_size_ > 0)
    {
        return file.readsome((char *) &unit_[0], sizeof(char) * unit_size_); // returns number of Read bits
    }
    else
    {
        return 0;
        //throw std::runtime_error("Error: Unit::Write: Could not Read chunk from file\n");
    }
}

void Unit::Write(std::ofstream &file)
{
    if(!unit_.empty() && unit_size_ > 0)
    {
        file.write((char *) &unit_[0], sizeof(char) * unit_size_);
        if(hash_)
            file << hash_;
    }
}

std::ostream& operator<<(std::ostream& out, const Unit& unit)
{
    out << unit.unit_;
    return out;
}

std::basic_string<char> Unit::Data()
{
    return std::basic_string<char>(unit_);
}
