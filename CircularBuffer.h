//
// Created by adron on 12/26/22.
//

#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H

template <typename Type, int Size>
class CircularBuffer {
public:
    [[nodiscard]] bool empty() const {
        return true;
    }

    [[nodiscard]] uint32_t count() const {
        return 0;
    }
};

#endif //CIRCULARBUFFER_CIRCULARBUFFER_H
