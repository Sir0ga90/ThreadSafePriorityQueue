// TSPriority_Queue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TSPriorQueue.h"

#define TS_QUEUE

static const int CONSUMERS = 4;
static const int TO_CONSUM = 3;
static const int TO_PRODUCE = CONSUMERS * TO_CONSUM;

#ifdef TS_QUEUE
using PriorityQueue = TSPriorQueue<int>;
#else 
using PriorityQueue = std::priority_queue<int>;
#endif

void produce(PriorityQueue& _tspq);
void consume(PriorityQueue& _tspq, int _id);
void tsPrint(std::string _msg);

/*==========================================================*/
/*==========================================================*/
int main() {

    PriorityQueue tsQueue;
    std::thread producerThread(std::bind(produce, std::ref(tsQueue)));

    std::vector<std::thread> threadVector;
    for (int i = 0; i < TO_CONSUM; i++) {
        std::thread consumer(std::bind(consume, std::ref(tsQueue), i + 1));
        threadVector.push_back(std::move(consumer));
    }

    producerThread.join();

    for (auto& thread : threadVector) {
        thread.join();
    }

    return EXIT_SUCCESS;
}


/*==========================================================*/
/*==========================================================*/
void produce(PriorityQueue& _tspq) {
    for (int i = 0; i < TO_PRODUCE; i++) {
        _tspq.push(i);
        std::ostringstream ostrstr;
        ostrstr << "num: " << i;
        tsPrint(ostrstr.str());
    }
}


/*==========================================================*/
void consume(PriorityQueue& _tspq, int _id) {
    for (int i = 0; i< CONSUMERS; i++) {
        auto elem = _tspq.top();
        std::ostringstream ostrostr;
        ostrostr << "out number: " << elem << "\t" << _id;
        _tspq.pop();
        tsPrint(ostrostr.str());
    }
}

/*==========================================================*/
void tsPrint(std::string _msg) {
    static std::mutex mutex;
    std::unique_lock<std::mutex> locker(mutex);
    std::cout << _msg << "\n";
}

