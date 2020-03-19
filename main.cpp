#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  //convert
#include <cstring>  //strcmp
#include <functional> //hash

/*
enum class colors
{
    red,
    blue,
    none,
};

std::ostream& operator<< (std::ostream &out, colors col)
{
    switch(col)
    {
        case colors::red  :  out << "\033[31m";
        case colors::blue :  out << "\033[34m";
        case colors::none :  out << "\033[0m";
        default          :  out.setstate(std::ios_base::failbit);
    }
    return out;
}
 */

namespace color
{
    char  red []= "\033[31m";
    char  blue[] = "\033[34m";
    char  none[] = "\033[0m";
}

constexpr bool test_mode = true;

class Unit
{
private:
    std::basic_string<char> unit;
    int unit_size;
    std::hash<std::basic_string<char>> hash_gen;
    size_t unit_hash;

    void init(unsigned int unit_size_in)
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
public:
    explicit Unit(int unit_size_in = 0):unit_size{unit_size_in},unit_hash{0}
    {
        init(unit_size_in);
    }
    explicit Unit(char *unit_size_str):unit_hash{0}
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
        init(unit_size);
    }
    ~Unit()
    {
        if(test_mode) printf("Destructor INT\n");
    }

    [[nodiscard]] int size() const
    {
        return unit_size;
    }
    [[nodiscard]] size_t hash() const
    {
        return unit_hash;
    }
    [[nodiscard]] std::basic_string<char> data() const
    {
        return unit;
    }

    void resize(int to_resize)
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
    void fill()
    {
        if(test_mode) printf("Fill\n");
        //!check unit, size
        try
        {
            if (!unit.empty())
                for (int k = unit.size(); k < unit_size; ++k)
                    unit.at(k) = '\0';
        }
        catch(const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << "\n";
        }
    }
    void gen()
    {
        if(test_mode) printf("GEN\n");

        //!check unit
        if(!unit.empty())
        unit_hash = hash_gen(unit);
    }

    void read(std::ifstream &file)
    {
        if(test_mode) printf("read\n");
        //!check size & file
        try
        {
            if(!unit.empty()&&unit_size>0)
            file.read((char*)&unit[0], sizeof(char) * unit_size);
            else throw std::exception();
        }
        catch(const std::exception &ex)
        {
            std::cout << color::red << "Error: " << ex.what() << color::none << "\n";
        }
    }

    void write(std::ofstream &file)
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

    void disp()
    {
        if(test_mode) printf("DISP\n");
        std::cout << unit << "\n";
    }

    void info()
    {
        std::cout << color::blue << "INFO:\n" << color::none;
        if(unit.empty()) printf("no data\n");
        else             printf("has data\n");
        std::cout << "Unit size is " << unit_size << "\n";
        std::cout << color::blue << "------------\n" << color::none;
    }
};

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    std::cout << color::blue;
    //check num of args
    if(argc > 4 || argc < 3)
    {
        std::cout << color::red <<
                  "Got " << argc << " arguments, but 3 or 4 needed\nTerminating..." <<
                  color::none << "\n";
        return 1;
    }

    std::string file_in_path = argv[1], file_out_path = argv[2];

    //check diffs btw in & out
    if(file_in_path == file_out_path)
    {
        std::cout << color::red << "Error: Cannot write incoming file in itself" << color::none << "\n";
        file_out_path = "out.f";
        std::cout << "File out: " << file_out_path << "\n";
    }

    std::ifstream fin(file_in_path,std::ios::binary);
    std::ofstream fout(file_out_path,std::ios::binary);

    //get size of file
    fin.seekg(0,std::ios::end);
    int file_size = fin.tellg();
    fin.seekg(0,std::ios::beg);

    Unit unit(argv[3]);
    if(test_mode) unit.info();

    int block_num = 1;
    int unit_num = file_size / unit.size();
    if(file_size % unit.size() > 0) ++unit_num;

    std::cout << "size of in file: " << file_size << " byte\n";
    std::cout << "Units number: " << color::blue << unit_num << color::none << "\n";

    //read -> write
    while(unit_num > 0)
    {
        //fill last unit
        if(unit_num == 1)
            unit.fill();

        if(test_mode) unit.info();
        unit.read(fin);
        // in
        if (test_mode)
        {
            std::cout << "----------------in " << block_num << "-----------------" << std::endl;
            unit.disp();
            printf("\n");
        }

        //generate hash
        unit.gen();
        std::cout << "[" << block_num << "]" << color::red << "HASH: " << color::blue << unit.hash() << color::none << std::endl;

        //write
        unit.write(fout);
        --unit_num;
        ++block_num;
    }

    fout.close();
    fin.close();

    //cat out
    if(test_mode)
    {
        std::cout << "\n\n\n";
        std::cout << "----------------out-----------------" << std::endl;
        std::string to_cat = "cat " + file_out_path;
        system(to_cat.c_str());
    }

    return 0;
}