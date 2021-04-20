#pragma once

#include <Arduino.h>

template <typename T>
class vector;

namespace utils {
    template <typename T>
    vector<T> makeVector(const unsigned int& maxSize) {
        vector<T> result;
        T* storageArray;
        storageArray = (T*)malloc(sizeof(T) * maxSize);
        result.setStorage(storageArray, maxSize, 0);
        return result;
    }
}