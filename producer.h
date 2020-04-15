//
// Created by kirill on 26.03.2020.
//

#ifndef SIGNATURE_PRODUCER_H
#define SIGNATURE_PRODUCER_H

#include <memory>
#include <utility>

#include "unit.h"
#include "fixed_queue.h"

class Producer
{
public:
    explicit Producer(std::shared_ptr<FixedQueue<Unit>> buffer, const std::string &name_of_in_file, int unit_size);
    void Run();
private:
    Unit unit_;
    std::shared_ptr<FixedQueue<Unit>> buffer_;
    std::ifstream fin_;
};
#endif //SIGNATURE_PRODUCER_H
