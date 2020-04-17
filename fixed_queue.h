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
    ///
    /// @brief Costructs fixed queue
    ///
    FixedQueue();
    ~FixedQueue() = default;

    ///
    /// @breif Pushes element in queue
    ///
    /// @param[in] to_push element to push
    ///
    /// @note Works only when queue is not full. Else waits till last element will be poped.
    ///
    void Push(T to_push);

    ///
    /// @breif Pops element from queue
    ///
    /// @return front element from queue
    ///
    /// @note Works only when queue is not empty. Else waits till element will be pushed or buffer will be killed.
    ///
    T Pop();

    ///
    /// @breif Check if queue is full
    ///
    /// @return true if queue is full, otherwise false
    ///
    [[nodiscard]] bool Full() const;

    ///
    /// @breif Check if queue is empty
    ///
    /// @return true if queue is empty, otherwise false
    ///
    [[nodiscard]] bool Empty() const;

    ///
    /// @breif Check if queue is dead
    ///
    /// @return true if queue is dead, otherwise false
    ///
    [[nodiscard]] bool Dead() const;

    ///
    /// @breif Kills queue
    ///
    /// @note Sets dead_ true and notifies condition variable
    ///
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
    std::unique_lock<std::mutex> ul(mut_);
    dead_ = true;
    this->cv_.notify_one();
}

#endif //SIGNATURE_FIXED_QUEUE_H
