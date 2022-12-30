//
// Created by adron on 12/26/22.
//

#include <gtest/gtest.h>

#include <iostream>
#include <thread>

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

TEST(CircularBuffer, CountHandlesOverflow) {
    auto buffer = CircularBuffer<int, 3>();
    EXPECT_EQ(buffer.count(), 0);

    buffer.push(42);
    EXPECT_EQ(buffer.count(), 1);

    buffer.push(1337);
    EXPECT_EQ(buffer.count(), 2);

    EXPECT_EQ(buffer.pop(), 42);
    EXPECT_EQ(buffer.count(), 1);

    buffer.push(0xdead);
    EXPECT_EQ(buffer.count(), 2);

    EXPECT_EQ(buffer.pop(), 1337);
    EXPECT_EQ(buffer.count(), 1);

    buffer.push(0xbeef);
    EXPECT_EQ(buffer.count(), 2);

    EXPECT_EQ(buffer.pop(), 0xdead);
    EXPECT_EQ(buffer.count(), 1);

    buffer.push(31415);
    EXPECT_EQ(buffer.count(), 2);

    EXPECT_EQ(buffer.pop(), 0xbeef);
    EXPECT_EQ(buffer.count(), 1);

    EXPECT_EQ(buffer.pop(), 31415);
    EXPECT_EQ(buffer.count(), 0);
}

void prod(CircularBuffer<int, 3> &buffer) {
    for(int count = 0; count < 1000; ++count) {
        std::cout << "push " << count << " - " << buffer.count() << std::endl;
        buffer.push(count);
    }
}

void cons(CircularBuffer<int, 3> &buffer) {
    for(int count = 0; count < 1000; ++count) {
        auto elem = buffer.pop();
        std::cout << "pop " << elem << " - " << buffer.count() << std::endl;
        EXPECT_EQ(elem, count);
    }
}

// Not reliable and repeatable test
TEST(CircularBuffer, MultiThreaded) {
    auto buffer = CircularBuffer<int, 3>();

    std::thread producer;
    producer = std::thread(prod, std::ref(buffer));

    cons(buffer);

    producer.join();
}

// just for manual evaluation to evaluate move semantics
struct Object {
    Object() { std::cout << "ctor" << std::endl; };
    Object(const Object &) { std::cout << "copy ctor" << std::endl; };
    Object &operator =(const Object &)  noexcept { std::cout << "copy" << std::endl; };
    Object(Object &&)  noexcept { std::cout << "move ctor" << std::endl; };
    Object &operator =(Object &&)  noexcept { std::cout << "move" << std::endl; };
};

TEST(CircularBuffer, moveTest) {
    auto buffer = CircularBuffer<Object, 3>();
    auto obj = Object{};
    buffer.push(Object{});
    buffer.push(obj);
    buffer.push(std::move(obj));

    auto ret = buffer.pop();
}