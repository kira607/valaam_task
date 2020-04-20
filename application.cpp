//
// Created by kirill on 14.04.2020.
//

#include "application.h"

Application::Application(const std::string& file_in, const std::string& file_out, int unit_size)
: producer_{buffer1_ptr_, file_in, unit_size},
  hash_gen_{buffer1_ptr_, buffer2_ptr_, unit_size},
  consumer_{buffer2_ptr_, file_out, unit_size}
{

}

void Application::Run()
{
    std::thread producer_thread(&Producer::Run, &producer_);
    std::thread hash_gen_thread(&HashGenerator::Run, &hash_gen_);
    std::thread consumer_thread(&Consumer::Run, &consumer_);
    producer_thread.join();
    hash_gen_thread.join();
    consumer_thread.join();
}
