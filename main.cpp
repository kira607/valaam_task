#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "test_mode.h"
#include "color.h"
#include "Unit.h"
#include "Producer.h"
#include "HashGen.h"

inline std::string intToString(int _int)
{
    std::string msg = reinterpret_cast<const char *>(_int);
    return msg;
}

int setUnitSize(int argc, char* argv[])
{
    //check num of args
    if(argc > 4 || argc < 3)
    {
        std::string msg = "Got ";
        msg+=intToString(argc);
        msg+=" arguments, but 3 or 4 needed\nTerminating...";
        throw std::runtime_error(msg);
    }
    else if(argc != 4)
    {
        throw std::runtime_error("Did not receive unit size. Setting default... (1MB)");
    }

    //convert unit size to int
    int unit_size;
    std::stringstream convert(argv[4]);
    if (!(convert >> unit_size))
    {
        throw std::runtime_error("Bad unit size. Setting default... (1MB)");
    }
    if(unit_size <= 0)
    {
        throw std::runtime_error("Bad unit size. Setting default... (1MB)");
    }

    return unit_size;
}

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    int unit_size;
    constexpr int default_unit_size = 1024*1024;

    try
    {
        unit_size = setUnitSize(argc,argv);
    }
    catch(std::exception &exception)
    {
        std::cout << color::red << exception.what() << color::none << '\n';
        unit_size = default_unit_size;
    }

    const unsigned char thread_num = std::thread::hardware_concurrency();
    std::cout << "I have " << (short)thread_num << " threads for you\n";

    std::string file_in_path = argv[1], file_out_path = argv[2];

    std::ifstream fin(file_in_path);
    std::ofstream fout(file_out_path);

    if(!fin.is_open())
    {
        std::cout << color::red << "Error: could not open " << file_in_path << color::none << "\n";
        return -100;
    }
    if(!fout.is_open())
    {
        std::cout << color::red << "Error: could not open " << file_out_path << color::none << "\n";
        return -150;
    }

    Unit unit;
    std::cout << unit << "\n";

    std::vector<Unit> buff1, buff2;
    constexpr unsigned int buffer_size = 10;
    Producer producer(buff1,fin);
    HashGen hashGen(buff1,buff2);
    Consumer consumer(buff2,fout);

    /*
    fin.seekg(0, std::ios::end);
    size_t file_in_size = fin.tellg();
    fin.seekg(0, std::ios::beg);
     */

    //Unit unit(argv[3]);

    //if(test_mode) unit.info();

    //int block_num = 1;
    ///int unit_num = (int)file_in_size / unit.size();
    ///if(file_in_size % unit.size() > 0) ++unit_num;
    ///std::cout << "size of in file: " << file_in_size << " byte\n";
    ///std::cout << "Units number: " << color::blue << unit_num << color::none << "\n";


    ////read -> write
    //while(int k = unit.read(fin))
    //{
    //    //fill last unit
    //
    //
    //    if(test_mode) unit.info();
    //    std::cout << "Read " << k << " bytes\n";
    //    // in
    //    if (test_mode)
    //    {
    //        std::cout << "----------------in " << block_num << "-----------------" << std::endl;
    //        unit.disp();
    //        printf("\n");
    //    }
    //
    //    //generate hash
    //    unit.gen();
    //
    //    if(test_mode)
    //    {
    //        std::cout << "[" << block_num << "]" << color::red << "HASH: " << color::blue << unit.hash() << color::none
    //                  << std::endl;
    //    }
    //
    //    //write
    //    unit.write(fout);
    //    unit.fill();
    //   /// --unit_num;
    //    ++block_num;
    //}
    //
    //fin.close();
    //fout.close();
    //
    ////cat out
    //if(test_mode)
    //{
    //    std::cout << "\n\n\n";
    //    std::cout << "----------------out-----------------" << std::endl;
    //    std::string to_cat = "cat " + file_out_path;
    //    system(to_cat.c_str());
    //}
    //

    return 0;
}