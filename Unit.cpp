//
// Created by kirill on 20.03.2020.
//

#include "Unit.h"

Unit::Unit(int unit_size_in):unit_size{unit_size_in},unit_hash{0}
{
    if(test_mode)
        std::cout << "CONSTRUCTOR, " << unit_size_in << "\n";

    unit.resize(unit_size_in, 0);
}

Unit::~Unit()
{
    if(test_mode) printf("Destructor\n");
}

[[nodiscard]] int Unit::size() const
{
    return unit_size;
}

[[nodiscard]] size_t Unit::hash() const
{
    return unit_hash;
}
[[nodiscard]] std::basic_string<char> Unit::data() const
{
    return unit;
}

void Unit::refill()
{
    unit.resize(unit_size);
}

void Unit::gen()
{
    if(test_mode) printf("GEN\n");

    //!check unit
    if(!unit.empty())
        unit_hash = hash_gen(unit);
}

size_t Unit::read(std::ifstream &file)
{
    if(test_mode) printf("READ\n");
    //!check size & file
    try
    {
        if(!unit.empty()&&unit_size>0)
            return file.readsome((char*)&unit[0], sizeof(char) * unit_size); //! returns num of read bits
        else throw std::exception();
    }
    catch(const std::exception &ex)
    {
        std::cout << color::red << "Error: " << ex.what() << color::none << "\n";
    }
}

void Unit::write(std::ofstream &file)
{
    if(test_mode) printf("WRITE\n");

    try
    {
        if(!unit.empty()&&unit_size>0)
        {
            file.write((char *) &unit[0], sizeof(char) * unit_size);
            if(unit_hash)
                file << unit_hash;
        }
        else throw std::exception();
    }
    catch(const std::exception &ex)
    {
        std::cout << color::red << "Error: " << ex.what() << color::none << "\n";
    }
}

void Unit::disp()
{
    if(test_mode) printf("DISP\n");
    std::cout << unit << "\n";
}

std::ostream& operator<<(std::ostream& out, const Unit& unit)
{
    out << unit;
    return out;
}