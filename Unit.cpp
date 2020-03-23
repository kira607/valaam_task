//
// Created by kirill on 20.03.2020.
//

#include "Unit.h"

void Unit::init(unsigned int unit_size_in)
{
    if(test_mode) printf("INIT, %d\n",unit_size_in);
    try
    {
        if(unit_size_in>0)
            unit.resize(unit_size_in,0);
        else throw std::exception(); //! set def unit size
    }
    catch(const std::exception &ex) // catch std::bad_alloc
    {
        std::cout << color::red << "Error: " << ex.what() << color::none << "\n";
        unit_size = 1024*1024;
        unit.resize(unit_size,0);
    }
}

Unit::Unit(int unit_size_in):unit_size{unit_size_in},unit_hash{0}
{
    Unit::init(unit_size_in);
}

Unit::Unit(char *unit_size_str):unit_hash{0}
{
    if(test_mode) printf("Constructor CHAR*, size:%s\n",unit_size_str);
    try
    {
        std::stringstream convert(unit_size_str);
        if (!(convert >> unit_size))
        {
            std::cout << color::red << "Bad unit size. Setting default... (1MB)\n" << color::none;
            unit_size = 1024*1024;
        }
        else
        {
            if(test_mode) printf("Convert succeed!\n");
            if(unit_size <= 0)
                throw std::exception();
            //std::cout << "Unit size: " << unit_size << " byte\n";
        }
    }
    catch(const std::exception &ex)
    {
        if(strcmp(ex.what(),"") == 0)
            std::cout << color::blue << "Did not receive unit size. Setting default... (1MB)\n" << color::none;
        else
            std::cout << color::red << "Bad unit size. Setting default... (1MB)\n" << color::none;

        unit_size = 1024*1024;
    }
    Unit::init(unit_size);
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

void Unit::resize(int to_resize)
{
    try
    {
        if(unit.empty()||to_resize>0)
            unit.resize(to_resize);
        else throw std::exception();
    }
    catch(const std::exception &ex) // catch std::bad_alloc
    {
        if(strcmp(ex.what(),"") == 0)
            std::cout << color::blue << "Error: bad resize" << color::none;
        else
            std::cout << color::red << "Error: " << ex.what() << color::none << "\n";
    }
}
void Unit::fill()
{
    if(test_mode) printf("FILL\n");
    //!check unit, size
    try
    {
        if (!unit.empty())
            for (int k = 0/*unit.size()*/; k < unit_size; ++k)
                unit.at(k) = '\0';
    }
    catch(const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
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
            return file.readsome((char*)&unit[0], sizeof(char) * unit_size); //! returns num of read bits!!!???
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

void Unit::info()
{
    std::cout << color::blue << "INFO:\n" << color::none;
    if(unit.empty()) printf("no data\n");
    else             printf("has data\n");
    std::cout << "Unit size is " << unit_size << "\n";
    std::cout << color::blue << "------------\n" << color::none;
}

