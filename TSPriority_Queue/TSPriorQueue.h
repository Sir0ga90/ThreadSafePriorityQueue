#pragma once

#include <queue>
#include <thread>
#include <mutex>

template <class T>
class TSPriorQueue {
public:
    void push(const T& _newElem);
    void pop();
    T top();
    size_t size();
    bool is_empty();

private:
    std::priority_queue<T> mPriorQueue;
    std::mutex mMutex;
    std::condition_variable mCondition;
};


/*==========================================================*/
template<class T>
inline void TSPriorQueue<T>::push(const T & _newElem) {
    std::unique_lock<std::mutex> localLock(mMutex);
    mPriorQueue.push(_newElem);
    localLock.unlock();
    mCondition.notify_one();
}


/*==========================================================*/
template<class T>
inline void TSPriorQueue<T>::pop() {
    std::unique_lock<std::mutex> localLock(mMutex);
    
    while (is_empty()) {
        mCondition.wait(localLock);
    }

    mPriorQueue.pop();
}


/*==========================================================*/
template<class T>
inline T TSPriorQueue<T>::top() {
    std::unique_lock<std::mutex> localLock(mMutex);
    while (is_empty()) {
        mCondition.wait(localLock);
    }
    auto topQueueVal = mPriorQueue.top();
    return topQueueVal;
}


/*==========================================================*/
template<class T>
inline size_t TSPriorQueue<T>::size() {
    return mPriorQueue.size();
}


/*==========================================================*/
template<class T>
inline bool TSPriorQueue<T>::is_empty() {
    return mPriorQueue.empty();
}
