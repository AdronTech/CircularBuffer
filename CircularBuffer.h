//
// Created by adron on 12/26/22.
//

#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H

#include <mutex>
#include <condition_variable>

template <typename Type, int Size>
class CircularBuffer {
    Type buffer[Size];
    uint32_t startIndex{0};
    // a variable for counting the elements was used instead of a start and end index,
    // because with a start and end index the case (start == end) could mean empty or full
    uint32_t nrOfElements{0};

    // this mutex is used to control access to the buffer and the count variable
    std::mutex mutex;
    // this condition variable is used to denote an element was pushed
    std::condition_variable wasPushed;
    // this condition variable is used to denote an element was popped
    std::condition_variable wasPopped;

    // helper methods
    uint32_t getEndIndex() {
        // offset startIndex by Size before modulo in order to prevent negative values
        return ((startIndex + Size) - nrOfElements) % Size;
    }

    bool _empty() {
        return nrOfElements == 0;
    }

    bool _full() {
        return nrOfElements == Size;
    }

public:
    /**
     * Pushes element onto buffer.
     * If buffer is full it waits until buffer is popped by other thread.
     * @param element to be pushed
     */
    void push(Type element) {
        std::unique_lock<std::mutex> lock(mutex);
        while(_full()) wasPopped.wait(lock); // wait for elements to be popped if full

        buffer[startIndex] = element;
        startIndex++;
        nrOfElements++;
        startIndex %= Size; // keep index within Size range

        wasPushed.notify_all(); // notify all threads that buffer was filled up
    }

    /**
     * Pops element from buffer
     * If buffer is empty it waits until there are elements pushed by other thread.
     * @return popped element
     */
    Type pop() {
        std::unique_lock<std::mutex> lock(mutex);
        while(_empty()) wasPushed.wait(lock); // wait for elements to be pushed if empty

        uint32_t endIndex = getEndIndex();
        Type element = buffer[endIndex];
        nrOfElements--;

        wasPopped.notify_all(); // notify all threads that buffer was emptied up
        return element;
    }

    /**
     * Current number of elements in buffer.
     * @return current element count
     */
    [[nodiscard]] uint32_t count() {
        std::unique_lock<std::mutex> lock(mutex);
        return nrOfElements;
    }

    /**
     * Is buffer empty.
     * @return true if buffer empty
     */
    [[nodiscard]] bool empty() {
        std::unique_lock<std::mutex> lock(mutex);
        return _empty();
    }

    /**
     * Is buffer full.
     * @return true if buffer full
     */
    [[nodiscard]] bool full() {
        std::unique_lock<std::mutex> lock(mutex);
        return _full();
    }
};

#endif //CIRCULARBUFFER_CIRCULARBUFFER_H
