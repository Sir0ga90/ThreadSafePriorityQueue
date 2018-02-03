#pragma once
#include "stdafx.h"

template <typename T>
class PriorityQueueDerived :
    public std::priority_queue<T> {
public:
    using std::priority_queue::priority_queue;  //inherit constructors

    void push(const T& _newElem) override;
    //void pop() override;
    //T top() override;
    //size_t size() override;
    //bool empty() override;


    PriorityQueueDerived();
    ~PriorityQueueDerived();
};

/*==========================================================*/
template<typename T>
void PriorityQueueDerived<T>::push(const T& _newElem) {

}
