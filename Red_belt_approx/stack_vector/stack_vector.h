#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if (a_size > N) {
            throw invalid_argument("Too_big");
        }
        size_ = a_size;
    }

    T& operator[](size_t index) {
        return *(&data[0] + index);
    }
    const T& operator[](size_t index) const{
        return *(&data[0] + index);
    }

    T* begin() {
        return &data[0];
    }
    T* end() {
        return &data[0] + size_;
    }
    const T* begin() const {
        return &data[0];
    }
    const T* end() const {
        return &data[0] + size_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return N;
    }

    void PushBack(const T& value) {
        if (size_ == N) {
            throw overflow_error("is_full");
        }
        data[size_] = value;
        size_++;
    }
    T PopBack() {
        if (size_ == 0) {
            throw underflow_error("is_empty");
        }
        T back = data[size_ - 1];
        size_--;
        return back;
    }

private:
    array<T, N> data;
    size_t size_;
};

