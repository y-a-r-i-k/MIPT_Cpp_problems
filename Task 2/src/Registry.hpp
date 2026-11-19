#pragma once
#include <array>
#include <stdexcept>

template<typename T, int Capacity>
class Registry {
private:
    std::array<T*, Capacity> data_{};
    int size_ = 0;

public:
  void add(T* item);
  int size() const;
  T* operator[](int index);
  void clear();
};

template<typename T, int Capacity>
void Registry<T, Capacity>::add(T* item) {
  if (size_ >= Capacity) {
    throw std::runtime_error("Registry is full");
  }
  data_[size_] = item;
  ++size_;
}

template<typename T, int Capacity>
int Registry<T, Capacity>::size() const {
  return size_;
}

template<typename T, int Capacity>
T* Registry<T, Capacity>::operator[](int index) {
  if (index < 0 || index >= size_) {
    throw std::runtime_error("Index out of range");
  }

  return data_[index];
}

template<typename T, int Capacity>
void Registry<T, Capacity>::clear() {
  size_ = 0;
}