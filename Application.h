//
// Created by kirill on 14.04.2020.
//

#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H

#include <memory>
#include <thread>

#include "Producer.h"
#include "HashGen.h"
#include "Consumer.h"

class Application
{
private:
    //buffers for units
    std::shared_ptr<FixedQueue<Unit>> buff1_ptr {new FixedQueue<Unit>};
    std::shared_ptr<FixedQueue<Unit>> buff2_ptr {new FixedQueue<Unit>};

    Producer producer;
    HashGen hashGen;
    Consumer consumer;
public:
    Application(const std::string& file_in, const std::string& file_out, int unit_size);
    void run();
};


#endif //UNTITLED_APPLICATION_H
