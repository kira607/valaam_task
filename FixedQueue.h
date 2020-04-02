//
// Created by kirill on 30.03.2020.
//

#ifndef UNTITLED_FIXEDQUEUE_H
#define UNTITLED_FIXEDQUEUE_H

#include <queue>
#include <condition_variable>

#include "Unit.h"

template <class T>
class FixedQueue
{
private:
    static constexpr int fixed_size = 10;
    std::queue<T> queue;
    std::mutex mut;
    std::condition_variable cv;
public:
    FixedQueue() = default;
    ~FixedQueue() = default;
    void push(T _to_push);
    T pop();
    T& front();
    T& back();
    [[nodiscard]] int size() const;
    [[nodiscard]] int fixedSize() const;
    [[nodiscard]] bool full() const;
    [[nodiscard]] bool empty() const;
};

template<class T>
void FixedQueue<T>::push(T _to_push)
{
    std::unique_lock<std::mutex> ul(mut);
    cv.wait(ul,[&]{return !this->full();});
    queue.push(_to_push);
    cv.notify_one();
}

template<class T>
T FixedQueue<T>::pop()
{
    std::unique_lock<std::mutex> ul(mut);
    cv.wait(ul,[&]{return !this->empty();});
    T tmp = front();
    queue.pop();
    return tmp;
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
    return queue.size() == 0;
}


#endif //UNTITLED_FIXEDQUEUE_H
