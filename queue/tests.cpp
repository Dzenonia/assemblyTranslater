#include "queue.h"
#include <gtest/gtest.h>
#include <queue>

TEST(Queue, Constructors) {
    Queue<int> lhs({1, 2, 3, 4}); // std::initializer_list
    Queue<int> rhs({5, 2, 3, 4}); // std::initializer_list
    EXPECT_EQ(lhs, Queue<int>({1, 2, 3, 4})); // check

    lhs = Queue<int>({4, 3, 2, 1}); // move-operator

    EXPECT_EQ(lhs, Queue<int>({4, 3, 2, 1})); // check

    lhs = rhs; // copy-operator

    EXPECT_EQ(lhs, rhs); // check

    lhs = std::move(rhs); // move-operator

    EXPECT_EQ(lhs, Queue<int>({5, 2, 3, 4})); // check

    EXPECT_TRUE(rhs.isEmpty()); // check that all rhs data move to lhs

    Queue<int> nhs = lhs; // copy constructor

    EXPECT_EQ(nhs.size(), 4); // check

    Queue<int> khs = std::move(nhs); // move constructor

    EXPECT_EQ(khs, lhs); // check

    EXPECT_TRUE(nhs.isEmpty()); // check that all nhs data in khs

    std::swap(lhs, rhs);
}

TEST(Queue, CheckTime) {
    const int cntIterations = 1'000'000;
    Queue<int> firstQueue({0});
    std::queue<int> secondQueue;

    auto startSecondQueue = clock();

    for (int i = 0; i < cntIterations; ++i) {
        secondQueue.push(0);
    }

    auto endSecondQueue = clock();

    auto startFirstQueue = clock();

    for (int i = 0; i < cntIterations; ++i) {
        firstQueue.push(0);
    }

    auto endFirstQueue = clock();

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "first: " << static_cast<double>(endFirstQueue - startFirstQueue) / CLOCKS_PER_SEC << '\n';
    std::cout << "second: " << static_cast<double>(endSecondQueue - startSecondQueue) / CLOCKS_PER_SEC << '\n';
}

TEST(Queue, PushPop) {
    std::queue<int> trueQueue;
    Queue<int> myQueue;

    trueQueue.push(2);
    trueQueue.push(13);
    trueQueue.push(13);
    trueQueue.pop();

    myQueue.push(2);
    myQueue.push(13);
    myQueue.push(13);
    myQueue.pop();

    EXPECT_EQ(myQueue.front(), trueQueue.front());
    EXPECT_EQ(myQueue.back(), trueQueue.back());
    EXPECT_EQ(myQueue.size(), trueQueue.size());
}

