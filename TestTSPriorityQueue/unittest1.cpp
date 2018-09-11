#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TSPriority_Queue/TSPriorQueue.h"
#include "../TSPriority_Queue/PriorityQueueDerived.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTSPriorityQueue {
    TEST_CLASS(UnitTest1) {
public:

    PriorityQueueDerived<int> _pq;

    TEST_METHOD(TestMethodPush) {
        int myInt = 8;
        _pq.push(myInt);
        Assert::AreEqual(_pq.top(), myInt);
    }

    TEST_METHOD(TestPriority) {
        std::vector<int> iVec{ 9, 20, 2 };
        for (auto i : iVec) {
            _pq.push(i);
        }

        Assert::AreEqual(_pq.top(), 20);
    }

    };
}