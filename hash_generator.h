//
// Created by kirill on 27.03.2020.
//

#ifndef SIGNATURE_HASH_GENERATOR_H
#define SIGNATURE_HASH_GENERATOR_H

#include <memory>
#include <utility>

#include "unit.h"
#include "fixed_queue.h"
#include "color.h"

class HashGenerator
{
public:
    ///
    /// @brief Constructs gash generator object.
    ///
    /// @param[in] buffer1 Pointer on buffer connected with Producer.
    /// @param[in] buffer2 Pointer on buffer connected with Consumer.
    /// @param[in] unit_size Size of unit in bytes.
    ///
    /// @return Constructed hash generator object
    ///
    HashGenerator(std::shared_ptr<FixedQueue<Unit>> buffer1, std::shared_ptr<FixedQueue<Unit>> buffer2, int unit_size);

    ///
    /// @brief Runs hash generator
    ///
    void Run();
private:
    ///
    /// @brief Generates hash for unit
    ///
    /// @param unit Unit to which will be generated hash
    ///
    /// @return Generated hash
    ///
    size_t GenerateHash(Unit& unit);
    std::shared_ptr<FixedQueue<Unit>> buffer1_;
    std::shared_ptr<FixedQueue<Unit>> buffer2_;
    std::hash<std::basic_string<char>> hash_generator_;
    Unit unit_;
};


#endif //SIGNATURE_HASH_GENERATOR_H
