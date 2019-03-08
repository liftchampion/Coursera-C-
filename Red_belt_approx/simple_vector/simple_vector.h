#pragma once

#include <cstdlib>
//#include <iostream>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() {
      data = nullptr;
      size_ = 0;
      capacity = 0;
  }
  explicit SimpleVector(size_t size) {
      data = new T[size];
      size_ = size;
      capacity = size;
  }
  ~SimpleVector() {
      delete[] data;
  }

  T& operator[](size_t index) {
      return data[index];
  }

  T* begin() {
      return data;
  }
  T* end() {
      return data + size_;
  }

  size_t Size() const {
      return size_;
  }
  size_t Capacity() const {
      return capacity;
  }
  void PushBack(const T& value) {
      //std::cerr << "push_back" << std::endl;
      if (size_ < capacity) {
          //std::cerr << "enough" << std::endl;
          data[size_] = value;
          size_++;
      }
      else {
          //std::cerr << "allocating new" << std::endl;
          T* new_data = new T[capacity * 2];
          //std::cerr << "new" << std::endl;
          for (size_t i = 0; i < size_; i++) {
              *(new_data + i) = *(data + i);

          }
          if (capacity == 0) {
              capacity = 1;
          }
          else {
              capacity *= 2;
          }
          delete[] data;
          data = new_data;
          data[size_] = value;
          size_++;
      }
  }

private:
    T* data;
    size_t size_;
    size_t capacity;
  // Добавьте поля для хранения данных вектора
};
