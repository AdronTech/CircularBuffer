//
// Created by adron on 12/26/22.
//

#include <gtest/gtest.h>
#include "CircularBuffer.h"

TEST(CircularBuffer, InitialEmpty) {
    auto buffer = CircularBuffer<int, 20>();
    EXPECT_TRUE(buffer.empty()) << "Buffer is not empty initially!";
}

TEST(CircularBuffer, NotEmptyAfterPush) {
    auto buffer = CircularBuffer<int, 20>();
    buffer.push(42);
    EXPECT_FALSE(buffer.empty()) << "Buffer should not be empty after push";
}

TEST(CircularBuffer, EmptyAfterPushAndPop) {
    auto buffer = CircularBuffer<int, 20>();
    buffer.push(42);
    auto elem = buffer.pop();
    EXPECT_EQ(elem, 42) << "Popped element should be equal to pushed element";
    EXPECT_TRUE(buffer.empty()) << "Buffer should be empty after popping pushed element";
}

TEST(CircularBuffer, InitialCountZero) {
    auto buffer = CircularBuffer<int, 20>();
    EXPECT_EQ(buffer.count(), 0) << "Buffer count is not zero initially!";
}

TEST(CircularBuffer, CountCorrectAfterPush) {
    auto buffer = CircularBuffer<int, 20>();
    buffer.push(42);
    EXPECT_EQ(buffer.count(), 1) << "Buffer count does not reflect number of pushes!";
}
TEST(CircularBuffer, CountCorrectAfterPushAndPop) {
    auto buffer = CircularBuffer<int, 20>();
    buffer.push(42);
    auto elem = buffer.pop();
    EXPECT_EQ(elem, 42) << "Popped element should be equal to pushed element";
    EXPECT_EQ(buffer.count(), 0) << "Buffer count should be zero after popping pushed element";
}