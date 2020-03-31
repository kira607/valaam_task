#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "test_mode.h"
#include "color.h"
#include "Unit.h"
#include "Producer.h"
#include "HashGen.h"
#include "FixedQueue.h"

enum error_code
{
    NOT_ENOUGH_ARGUMENTS,
    FILE_IN_NOT_EXISTS,
    FILE_OUT_NOT_EXISTS,
};

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    int unit_size;
    constexpr int default_unit_size = 1024*1024;

    //check args
    if(argc > 4 || argc < 3)
    {
        std::cout << color::red << "Got " << argc <<
        " arguments, but 3 or 4 needed\nTerminating..." <<
        color::none;
        return NOT_ENOUGH_ARGUMENTS;
    }
    else if(argc != 4) // same as argc == 3
    {
        std::cout << color::blue << "Did not receive unit size. Setting default... (1MB)" << color::none << '\n';
        unit_size = default_unit_size;
    }
    else //convert unit size to int
    {
        std::stringstream convert(argv[3]);
        if (!(convert >> unit_size))
        {
            std::cout << color::red << "Bad unit size. Setting default... (1MB)" << color::none << '\n';
            unit_size = default_unit_size;
        }
        if(unit_size <= 0)
        {
            std::cout << color::red << "Bad unit size. Setting default... (1MB)" << color::none << '\n';
            unit_size = default_unit_size;
        }

    }

    std::string file_in_path = argv[1], file_out_path = argv[2];

    //check files
    if(!std::ifstream(file_in_path).is_open())
    {
        std::cout << color::red << "Error: could not open " << color::blue << file_in_path << color::red << "\nTerminating\n" << color::none;
        return FILE_IN_NOT_EXISTS;
    }
    if(!std::ofstream(file_out_path).is_open())
    {
        std::cout << color::red << "Error: could not open " << color::blue << file_out_path << color::red << "\nTerminating\n" << color::none;
        return FILE_OUT_NOT_EXISTS;
    }

    //////////////////////////////////////
    /// HERE WILL BE ARGUMENTS MANAGER ///
    //////////////////////////////////////

    ///DO I NEED THIS MESSAGE? PROBABLY NO...
    const unsigned char thread_num = std::thread::hardware_concurrency();
    std::cout << "This computer has " << color::blue << (short)thread_num << color::none << " threads\n";

    std::shared_ptr<FixedQueue<Unit>> buff1_ptr(new FixedQueue<Unit>);
    std::shared_ptr<FixedQueue<Unit>> buff2_ptr(new FixedQueue<Unit>);

    Producer producer(buff1_ptr, file_in_path, unit_size);









/*
    HashGen hashGen(buff1,buff2);
    Consumer consumer(buff2,fout);


    fin.seekg(0, std::ios::end);
    size_t file_in_size = fin.tellg();
    fin.seekg(0, std::ios::beg);


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

*/

    return 0;
}