#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue
{
public:
    explicit ThreadSafeQueue(std::size_t maxSize = 5)
        : maxSize_(maxSize)
    {
    }

    bool push(T item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        notFull_.wait(lock, [this]()
        {
            return queue_.size() < maxSize_ || closed_;
        });

        if (closed_)
        {
            return false;
        }

        queue_.push(std::move(item));

        notEmpty_.notify_one();

        return true;
    }

    bool waitAndPop(T& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        notEmpty_.wait(lock, [this]()
        {
            return !queue_.empty() || closed_;
        });

        if (queue_.empty())
        {
            return false;
        }

        item = std::move(queue_.front());
        queue_.pop();

        notFull_.notify_one();

        return true;
    }

    void close()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
        }

        notEmpty_.notify_all();
        notFull_.notify_all();
    }

private:
    std::queue<T> queue_;

    std::size_t maxSize_;

    std::mutex mutex_;

    std::condition_variable notEmpty_;
    std::condition_variable notFull_;

    bool closed_ = false;
};

#endif
