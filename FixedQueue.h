//
// Created by kirill on 30.03.2020.
//

#ifndef UNTITLED_FIXEDQUEUE_H
#define UNTITLED_FIXEDQUEUE_H

#include <queue>
#include "Unit.h"

template <class T>
class FixedQueue
{
private:
    static constexpr int size = 10;
    std::queue<T> queue;
public:
    FixedQueue() = default;
    ~FixedQueue() = default;
    void push(T _to_push);
    void pop();
    T front() const;
    T bach() const;
};




#endif //UNTITLED_FIXEDQUEUE_H
