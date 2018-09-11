#pragma once
#include "stdafx.h"

template <typename T>
class PriorityQueueDerived :
    public std::priority_queue<T> {
public:
    using std::priority_queue<T>::priority_queue;  //inherit constructors

    void push(const T& _newElem);
    void pop();
    T top();
    size_t size();
    bool empty();
    //~PriorityQueueDerived();

private:
    std::mutex mMutex;
    std::condition_variable mCondition;
};

/*==========================================================*/
template<typename T>
void PriorityQueueDerived<T>::push(const T& _newElem) {
    std::unique_lock<std::mutex> localLock(mMutex);
    priority_queue::push(_newElem);
    localLock.unlock();
    mCondition.notify_one();
}

/*==========================================================*/
template<class T>
inline void PriorityQueueDerived<T>::pop() {
    std::unique_lock<std::mutex> localLock(mMutex);

    while (empty()) {
        mCondition.wait(localLock);
    }

    priority_queue::pop();
}


/*==========================================================*/
template<class T>
inline T PriorityQueueDerived<T>::top() {
    std::unique_lock<std::mutex> localLock(mMutex);
    while (empty()) {
        mCondition.wait(localLock);
    }
    auto topQueueVal = priority_queue::top();
    return topQueueVal;
}


/*==========================================================*/
template<class T>
inline size_t PriorityQueueDerived<T>::size() {
    std::unique_lock<std::mutex> localLock(mMutex);
    return priority_queue::size();
}


/*==========================================================*/
template<class T>
inline bool PriorityQueueDerived<T>::empty() {
    return priority_queue::empty();
}
