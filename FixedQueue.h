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
    bool is_dead;
public:
    FixedQueue();
    ~FixedQueue() = default;

    void push(T _to_push);
    T pop();

    [[nodiscard]] bool full() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] bool dead() const;
    void kill();
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
    T tmp = queue.front();
    queue.pop();
    cv.notify_one();
    return tmp;
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

template<class T>
FixedQueue<T>::FixedQueue():is_dead{false}
{

}

template<class T>
bool FixedQueue<T>::dead() const
{
    return is_dead;
}

template<class T>
void FixedQueue<T>::kill()
{
    is_dead = true;
}

#endif //UNTITLED_FIXEDQUEUE_H
