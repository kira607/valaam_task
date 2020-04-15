//
// Created by kirill on 14.04.2020.
//

#ifndef SIGNATURE_APPLICATION_H
#define SIGNATURE_APPLICATION_H

#include <memory>
#include <thread>

#include "producer.h"
#include "hash_generator.h"
#include "consumer.h"

class Application
{
public:
    Application(const std::string& file_in, const std::string& file_out, int unit_size);
    void Run();
private:
    //buffers for units
    std::shared_ptr<FixedQueue<Unit>> buffer1_ptr_ {new FixedQueue<Unit>};
    std::shared_ptr<FixedQueue<Unit>> buffer2_ptr_ {new FixedQueue<Unit>};

    Producer producer_;
    HashGenerator hash_gen_;
    Consumer consumer_;
};


#endif //SIGNATURE_APPLICATION_H
