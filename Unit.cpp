//
// Created by kirill on 20.03.2020.
//

#include "Unit.h"

Unit::Unit(int unit_size_in):unit_size{unit_size_in},unit_hash{0}
{
    unit.resize(unit_size_in, 0);
}

void Unit::refill()
{
    for(auto &elem:unit)
    {
        elem = 0;
    }
}

void Unit::setHash(size_t _hash)
{
    unit_hash = _hash;
}

size_t Unit::read(std::ifstream &file)
{
    if(!unit.empty()&&unit_size>0)
    {
        return file.readsome((char *) &unit[0], sizeof(char) * unit_size); // returns number of read bits
    }
    else
    {
        throw std::runtime_error("Error: Unit::write: Could not read chunk from file\n");
    }
}

void Unit::write(std::ofstream &file)
{
    if(!unit.empty()&&unit_size>0)
    {
        file.write((char *) &unit[0], sizeof(char) * unit_size);
        if(unit_hash)
            file << unit_hash;
    }
    else
    {
       // throw std::runtime_error("Error: Unit::write: Could not write chunk in file\n");
    }
}

std::ostream& operator<<(std::ostream& out, const Unit& unit)
{
    out << unit.unit;
    return out;
}

std::basic_string<char> Unit::data()
{
    return std::basic_string<char>(unit);
}
