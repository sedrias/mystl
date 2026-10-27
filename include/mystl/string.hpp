#pragma once

#include <cstddef>
#include <utility>

namespace my {
class string {
  private:
    char* ptr_{};
    std::size_t capacity_{sso_capacity_};
    std::size_t size_{};
    static constexpr std::size_t sso_capacity_{15};
    char buf_[sso_capacity_ + 1]{};
    [[nodiscard]] bool is_small() const { return capacity_ <= sso_capacity_; }
    [[nodiscard]] char* data() { return is_small() ? buf_ : ptr_; }
    [[nodiscard]] const char* data() const { return is_small() ? buf_ : ptr_; }

  public:
    explicit string(const char* prompt) {
        std::size_t len{};
        while (prompt[len] != '\0') {
            ++len;
        }
        size_ = len;
        if (len > sso_capacity_) {
            ptr_ = new char[len + 1];
            capacity_ = len;
        }
        for (std::size_t i{0}; i < size_; ++i) {
            data()[i] = prompt[i];
        }
        data()[len] = '\0';
    }
    ~string() { delete[] ptr_; }
    string() = default;
    [[nodiscard]] std::size_t capacity() const { return capacity_; }
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] const char* c_str() const { return data(); }
    char& operator[](std::size_t index) { return data()[index]; }
    const char& operator[](std::size_t index) const { return data()[index]; }
    string(const string& other) { *this = other; }
    string& operator=(const string& other) {
        if (this == &other) {
            return *this;
        }
        delete[] ptr_;
        ptr_ = nullptr;
        capacity_ = sso_capacity_;
        size_ = other.size_;
        if (size_ > sso_capacity_) {
            ptr_ = new char[size_ + 1];
            capacity_ = size_;
        }
        for (std::size_t i{0}; i < size_; ++i) {
            data()[i] = other[i];
        }
        data()[size_] = '\0';
        return *this;
    }
    string& operator=(string&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] ptr_;
        size_ = other.size_;
        other.size_ = 0;
        if (other.is_small()) {
            ptr_ = nullptr;
            capacity_ = sso_capacity_;
            for (std::size_t i{0}; i < size_; ++i) {
                data()[i] = other[i];
            }
            data()[size_] = '\0';
        } else {
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
            capacity_ = other.capacity_;
            other.capacity_ = sso_capacity_;
        }
        return *this;
    }
    string(string&& other) noexcept { *this = std::move(other); }
    void reserve(std::size_t n) {
        if (n > capacity_) {
            char* new_data{new char[n + 1]};
            for (std::size_t i{0}; i < size_; ++i) {
                new_data[i] = data()[i];
            }
            delete[] ptr_;
            ptr_ = new_data;
            capacity_ = n;
            new_data[size_] = '\0';
        }
    }
    void push_back(const char c) {
        if (size_ == capacity_) {
            std::size_t new_capacity{capacity_ == 0 ? 1 : capacity_ * 2};
            reserve(new_capacity);
        }
        data()[size_] = c;
        ++size_;
        data()[size_] = '\0';
    }
};
} // namespace my
