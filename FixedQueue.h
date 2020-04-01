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
    static constexpr int fixed_size = 10;
    std::queue<T> queue;
public:
    FixedQueue() = default;
    ~FixedQueue() = default;
    bool push(T _to_push);
    void pop();
    T& front();
    T& back();
    [[nodiscard]] int size() const;
    [[nodiscard]] int fixedSize() const;
    [[nodiscard]] bool full() const;
    [[nodiscard]] bool empty() const;
};

template<class T>
bool FixedQueue<T>::push(T _to_push)
{
    if(queue.size() < fixed_size)
        queue.push(_to_push);
}

template<class T>
void FixedQueue<T>::pop()
{
    if(queue.size() > 1)
        queue.pop();
}

template<class T>
T& FixedQueue<T>::front()
{
    return queue.front();
}

template<class T>
T& FixedQueue<T>::back()
{
    return queue.back();
}

template<class T>
int FixedQueue<T>::size() const
{
    return queue.size();
}

template<class T>
int FixedQueue<T>::fixedSize() const
{
    return fixed_size;
}

template<class T>
bool FixedQueue<T>::full() const
{
    return fixed_size == queue.size();
}

template<class T>
bool FixedQueue<T>::empty() const
{
    return queue.size();
}


#endif //UNTITLED_FIXEDQUEUE_H
