#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace my {
template <typename T> class vector {
  private:
    T* data_{};
    std::size_t size_{};
    std::size_t capacity_{};

  public:
    vector(std::initializer_list<T> stack) {
        data_ = new T[stack.size()];
        capacity_ = stack.size();
        size_ = stack.size();
        std::size_t count{0};
        for (const T& one : stack) {
            data_[count] = one;
            ++count;
        }
    }
    vector() = default;
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] std::size_t capacity() const { return capacity_; }
    ~vector() { delete[] data_; }
    void push_back(const T& value) {
        if (size_ == capacity_) {
            std::size_t new_capacity{capacity_ == 0 ? 1 : capacity_ * 2};
            reserve(new_capacity);
        }
        data_[size_] = value;
        ++size_;
    }
    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range{"at() out of range"};
        }
        return data_[index];
    }
    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range{"const at() out of range"};
        }
        return data_[index];
    }
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range{"pop_back() size_ is empty"};
        }
        --size_;
    }
    [[nodiscard]] bool empty() const { return size_ == 0; }
    void clear() { size_ = 0; }
    void reserve(std::size_t n) {
        if (n > capacity_) {
            T* new_data{new T[n]};
            for (std::size_t i{0}; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = n;
        }
    }
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
    vector(const vector& other) { *this = other; }
    vector& operator=(const vector& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        reserve(other.size());
        for (std::size_t i{0}; i < other.size(); ++i) {
            data_[i] = other[i];
        }
        size_ = other.size();
        return *this;
    }
    vector(vector&& other) noexcept { *this = std::move(other); }
    vector& operator=(vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        other.size_ = 0;
        capacity_ = other.capacity_;
        other.capacity_ = 0;
        data_ = other.data_;
        other.data_ = nullptr;
        return *this;
    }
};
} // namespace my
