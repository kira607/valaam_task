//
// Created by kirill on 27.03.2020.
//

#ifndef SIGNATURE_CONSUMER_H
#define SIGNATURE_CONSUMER_H

#include <memory>
#include <utility>

#include "unit.h"
#include "fixed_queue.h"

class Consumer
{
public:
    ///
    /// @brief Constructs consumer.
    ///
    /// @param[in] buffer Pointer on buffer.
    /// @param[in] name_of_out_file name of file where to write.
    /// @param[in] unit_size size of unit in bytes.
    ///
    explicit Consumer(std::shared_ptr<FixedQueue<Unit>> buffer, const std::string &name_of_out_file, int unit_size);

    ///
    /// @brief Runs consumer.
    ///
    void Run();
private:
    Unit unit_;
    std::shared_ptr<FixedQueue<Unit>> buffer_;
    std::ofstream file_out_;
};


#endif //SIGNATURE_CONSUMER_H
