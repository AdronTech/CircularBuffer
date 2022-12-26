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
};

#endif //CIRCULARBUFFER_CIRCULARBUFFER_H
