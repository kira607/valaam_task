#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  //convert
#include <cstring>  //strcmp
#include <functional> //hash
#include <utility>


enum class color
{
    red,
    blue,
    none,
};

std::ostream& operator<< (std::ostream &out, color col)
{
    switch(col)
    {
        case color::red  :  out << "\033[31m"; break;
        case color::blue :  out << "\033[34m"; break;
        case color::none :  out << "\033[0m" ; break;
        default           :  out.setstate(std::ios_base::failbit); break;
    }
    return out;
}

/*
namespace color
{
    char  red []= "\033[31m";
    char  blue[] = "\033[34m";
    char  none[] = "\033[0m";
}
*/
constexpr bool test_mode = false;

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

class Files
{
private:
    std::ifstream fin;
    std::ofstream fout;
    std::string file_in_name;
    std::string file_out_name;
    int file_in_size;

    static bool fileExist(const std::string &name)
    {
        std::fstream tmp(name,std::ios::in);

        if(tmp.is_open())
        {
            tmp.close();
            return true;
            /*
            std::cout << color::red << "File \"" << file_out_name << "\" already exists!\n" <<
                      color::blue << "Are you sure want to rewrite \"" << file_out_name << "\"? (y,n): " << color::none;
            char ch;
            std::cin >> ch;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (ch != 'y') {
                std::cout << color::red << "Terminating..." << color::none << std::endl;
                tmp.close();
                return ;
            } else
                std::cout << color::blue << "Opening..." << color::none << std::endl;
                */
        }
        tmp.close();
        return false;
    }
public:
    explicit Files(std::string in = "", std::string out = ""):
    file_in_name{std::move(in)},file_out_name{std::move(out)},file_in_size{0}
    {
        // two files with same not empty names
        if(file_out_name == file_in_name && !file_in_name.empty())
        {
            file_out_name = "out.f";
        }
        if(!file_in_name.empty())
        {
            open_in(file_in_name);
        }
        if(!file_out_name.empty())
        {
            open_out(file_out_name);
        }
    }
    ~Files()
    {
        fin.close();
        fout.close();
    }
    void open_in(const std::string &name)
    {
        if(fin.is_open() && name == file_in_name)
        {
            return;
        }
        fin.open(name);
        if(!fin.is_open())
        {
            std::cout << color::red << "Error: couldn't open \"" << name << "\"\n" << color::none;
            fin.close();
            file_in_name = "";
        }
        else
        {
            file_in_name = name;
        }
    }
    void open_out(const std::string &name)
    {
        if(fout.is_open() && name == file_out_name)
        {
            return;
        }
        try
        {
            if (fileExist(name))
                throw std::exception();

            fout.open(name);
            if (!fout.is_open())
            {
                std::cout << color::red << "Error: couldn't open \"" << file_in_name << "\"\n" << color::none;
                fout.close();
                file_out_name = "";
            }
            else
            {
                file_out_name = name;
            }
        }
        catch(const std::exception &ex)
        {
            //file exists, what should program do???
            //what should I do???
            //I want to avoid rewriting an existing file
        }
    }
    unsigned int size_in()
    {
        if(fin.is_open())
        {
            fin.seekg(0, std::ios::end);
            file_in_size = fin.tellg();
            fin.seekg(0, std::ios::beg);
            return file_in_size;
        }
        else return 0;
    }

    std::ifstream &in()
    {
        return fin;
    }
    std::ofstream &out()
    {
        return fout;
    }
    const std::string &inName()
    {
        return file_in_name;
    }
    const std::string &outName()
    {
        return file_out_name;
    }

    void closeAll()
    {
        fin.close();
        fout.close();
    }
};

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    //check num of args
    if(argc > 4 || argc < 3)
    {
        std::cout << color::red <<
                  "Got " << argc << " arguments, but 3 or 4 needed\nTerminating..." <<
                  color::none << "\n";
        return 1;
    }

    Files files(argv[1],argv[2]);
    Unit unit(argv[3]);

    if(test_mode) unit.info();

    int block_num = 1;
    int unit_num = (int)files.size_in() / unit.size();
    if(files.size_in() % unit.size() > 0) ++unit_num;

    std::cout << "size of in file: " << files.size_in() << " byte\n";
    std::cout << "Units number: " << color::blue << unit_num << color::none << "\n";

    //read -> write
    while(unit_num > 0)
    {
        //fill last unit
        if(unit_num == 1)
            unit.fill();

        if(test_mode) unit.info();
        unit.read(files.in());
        // in
        if (test_mode)
        {
            std::cout << "----------------in " << block_num << "-----------------" << std::endl;
            unit.disp();
            printf("\n");
        }

        //generate hash
        unit.gen();

        if(test_mode)
        std::cout << "[" << block_num << "]" << color::red << "HASH: " << color::blue << unit.hash() << color::none << std::endl;

        //write
        unit.write(files.out());
        --unit_num;
        ++block_num;
    }

    files.closeAll();

    //cat out
    if(test_mode)
    {
        std::cout << "\n\n\n";
        std::cout << "----------------out-----------------" << std::endl;
        std::string to_cat = "cat " + files.outName();
        system(to_cat.c_str());
    }

    return 0;
}