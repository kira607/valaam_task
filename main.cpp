#include <iostream>
#include <string>
#include <utility> //move
#include <thread>

#include "test_mode.h"
#include "color.h"
#include "Unit.h"

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
    const unsigned char thread_num = std::thread::hardware_concurrency();
    std::cout << "I have " << (short)thread_num << " threads for you\n";
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
        {
            std::cout << "[" << block_num << "]" << color::red << "HASH: " << color::blue << unit.hash() << color::none
                      << std::endl;
        }

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