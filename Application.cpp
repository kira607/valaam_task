//
// Created by kirill on 14.04.2020.
//

#include "Application.h"

Application::Application(const std::string& file_in, const std::string& file_out, int unit_size)
:producer(buff1_ptr,file_in,unit_size),
hashGen(buff1_ptr,buff2_ptr,unit_size),
consumer(buff2_ptr,file_out,unit_size)
{

}

void Application::run()
{
    std::thread producer_thread(&Producer::run, &producer);
    std::thread hash_gen_thread(&HashGen::run, &hashGen);
    std::thread consumer_thread(&Consumer::run, &consumer);
    producer_thread.join();
    hash_gen_thread.join();
    consumer_thread.join();
}
