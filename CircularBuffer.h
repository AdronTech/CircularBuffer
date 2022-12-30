//
// Created by adron on 12/26/22.
//

#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H

template <typename Type, int Size>
class CircularBuffer {
    Type buffer[Size];
    uint32_t startIndex;
    uint32_t endIndex;

public:
    void push(Type element) {
        buffer[startIndex] = element;
        startIndex++;
        startIndex %= Size;
    }

    Type pop() {
        Type element = buffer[endIndex];
        endIndex++;
        endIndex %= Size;
        return element;
    }

    [[nodiscard]] uint32_t count() const {
        if (startIndex < endIndex) {
            return (startIndex + Size) - endIndex;
        }
        return startIndex - endIndex;
    }

    [[nodiscard]] bool empty() const {
        return count() == 0;
    }
};

#endif //CIRCULARBUFFER_CIRCULARBUFFER_H
