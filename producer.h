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
    ///
    /// @brief Constructs producer
    ///
    /// @param buffer Pointer on buffer where to push read units
    /// @param name_of_in_file Name of file from which read
    /// @param unit_size Size of unit in bytes
    ///
    /// @return Constructed producer object
    ///
    explicit Producer(std::shared_ptr<FixedQueue<Unit>> buffer, const std::string &name_of_in_file, int unit_size);

    ///
    /// @breif Runs producer
    ///
    void Run();
private:
    Unit unit_;
    std::shared_ptr<FixedQueue<Unit>> buffer_;
    std::ifstream fin_;
};
#endif //SIGNATURE_PRODUCER_H
