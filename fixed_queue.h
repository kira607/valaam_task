//
// Created by kirill on 30.03.2020.
//

#ifndef SIGNATURE_FIXED_QUEUE_H
#define SIGNATURE_FIXED_QUEUE_H

#include <queue>
#include <condition_variable>

#include "unit.h"

template <class T>
class FixedQueue
{
public:
    FixedQueue();
    ~FixedQueue() = default;

    void Push(T _to_push);
    T Pop();

    [[nodiscard]] bool Full() const;
    [[nodiscard]] bool Empty() const;
    [[nodiscard]] bool Dead() const;
    void Kill();
private:
    static constexpr int kFixedSize = 10;
    std::queue<T> queue_;
    std::mutex mut_;
    std::condition_variable cv_;
    bool dead_;
};

template<class T>
FixedQueue<T>::FixedQueue()
:dead_{false}
{

}

template<class T>
void FixedQueue<T>::Push(T to_push)
{
    std::unique_lock<std::mutex> ul(mut_);
    cv_.wait(ul, [&]{return !this->Full();});
    queue_.push(to_push);
    cv_.notify_one();
}

template<class T>
T FixedQueue<T>::Pop()
{
    std::unique_lock<std::mutex> ul(mut_);
    cv_.wait(ul, [&]
    {
        if(!this->Dead())
        {
            return !this->Empty();
        }
        return true;
    });
    if(this->Dead() && this->Empty())
    {
        return T{};
    }
    T tmp = queue_.front();
    queue_.pop();
    cv_.notify_one();
    return tmp;
}

template<class T>
bool FixedQueue<T>::Full() const
{
    return kFixedSize == queue_.size();
}

template<class T>
bool FixedQueue<T>::Empty() const
{
    return queue_.size() == 0;
}

template<class T>
bool FixedQueue<T>::Dead() const
{
    return dead_;
}

template<class T>
void FixedQueue<T>::Kill()
{
    dead_ = true;
    this->cv_.notify_one();
}

#endif //SIGNATURE_FIXED_QUEUE_H
