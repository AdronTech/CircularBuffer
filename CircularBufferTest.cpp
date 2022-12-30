//
// Created by adron on 12/26/22.
//

#include <gtest/gtest.h>
#include "CircularBuffer.h"

TEST(CircularBuffer, InitialEmpty) {
    auto buffer = CircularBuffer<int, 20>();
    EXPECT_TRUE(buffer.empty()) << "Buffer is not empty initially!";
}

TEST(CircularBuffer, InitialCountZero) {
    auto buffer = CircularBuffer<int, 20>();
    EXPECT_EQ(buffer.count(), 0) << "Buffer count is not zero initially!";
}