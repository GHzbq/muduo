/**
 * 实现一个线程安全的计数器
 * 对于 MutexLock 和 MutexLockGuard 稍后再说
 * */
#include <iostream>
#include <boost/noncopyable.hpp>

class Counter : boost::noncopyable
{
public:
    Counter()
        : value_(0)
    {}

    int64_t value() const;

    int64_t getAndIncrease();

private:
    int64_t value_;
    mutable MutexLock mutex_;
};

int64_t Counter::value() const
{
    MutexLockGuard lock(mutex_);
    return value_;
}

int64_t Counter::getAndIncrease()
{
    MutexLockGuard lock(mutex_);
    int64_t ret = value_++;
    return ret;
}

// In a real world, atomic operations are preferred.
// 当然在实际项目中，这个 class 用原子操作更合理，这里用锁仅仅为了举例

