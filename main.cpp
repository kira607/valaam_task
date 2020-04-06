#include <iostream>
#include <string>
#include <thread>
//#include <chrono>

#include "color.h"
#include "Producer.h"
#include "HashGen.h"
#include "Consumer.h"
#include "FixedQueue.h"

enum error_code
{
    SUCCESS = 0,
    NOT_ENOUGH_ARGUMENTS,
    FILE_IN_NOT_EXISTS,
    FILE_OUT_NOT_EXISTS,
};

//requires minimum 3 arguments
//maximum 4
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    std::ofstream f("BIGFILE_4GB");
    for(unsigned long i = 0; i < 4294967296; ++i)
    {
        f << rand()%10;
    }
    ///auto start = std::chrono::high_resolution_clock::now();
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
        std::cout << color::red << "Error: could not open " << color::blue <<
        file_in_path << color::red << "\nTerminating\n" << color::none;
        return FILE_IN_NOT_EXISTS;
    }
    if(!std::ofstream(file_out_path).is_open())
    {
        std::cout << color::red << "Error: could not open " << color::blue <<
        file_out_path << color::red << "\nTerminating\n" << color::none;
        return FILE_OUT_NOT_EXISTS;
    }

    ///const unsigned char thread_num = std::thread::hardware_concurrency();
    ///std::cout << "This computer has " << color::blue << (short) thread_num << color::none << " threads\n";

    //buffers for units
    std::shared_ptr<FixedQueue<Unit>> buff1_ptr(new FixedQueue<Unit>);
    std::shared_ptr<FixedQueue<Unit>> buff2_ptr(new FixedQueue<Unit>);

    //init classes
    Producer producer(buff1_ptr, file_in_path, unit_size);
    HashGen hashGen(buff1_ptr,buff2_ptr,unit_size);
    Consumer consumer(buff2_ptr,file_out_path,unit_size);

    //launch threads
    std::thread producer_thread(&Producer::run,&producer);
    std::thread hash_gen_thread(&HashGen::run,&hashGen);
    std::thread consumer_thread(&Consumer::run,&consumer);
    producer_thread.join();
    hash_gen_thread.join();
    consumer_thread.join();

    ///auto end = std::chrono::high_resolution_clock::now();
    ///std::cout << "Proccess took " << (end-start).count() << " nanoseconds\n";

    return SUCCESS;
}

//while(18446744073709551615UL == -1)

/*
while(producer.run())
{
    hashGen.run();
    consumer.run();
}
 */