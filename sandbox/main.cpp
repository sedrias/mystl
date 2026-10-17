#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace my {
template <typename T> class vector {
  private:
    T* data_{};
    std::size_t size_{};
    std::size_t capacity_{};

  public:
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] std::size_t capacity() const { return capacity_; }
    ~vector() { delete[] data_; }
    void push_back(const T& value) {
        if (size_ == capacity_) {
            std::size_t new_capacity{capacity_ == 0 ? 1 : capacity_ * 2};
            T* new_data{new T[new_capacity]};
            for (std::size_t i{0}; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
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
};
} // namespace my

int main() {
    my::vector<int> test{};
    test.push_back(10);
    test.push_back(20);
    test.push_back(30);
    std::cout << "test[1]: " << test[1] << '\n';
    test[1] = 99;
    std::cout << "test[1]: " << test[1] << '\n';
    const my::vector<int>& view = test;
    std::cout << "view[0]: " << view[0] << '\n';
    std::cout << "test.at(1): " << test.at(1) << '\n';
    try {
        std::cout << "test.at(10): " << test.at(10) << '\n';
    } catch (const std::out_of_range& err) {
        std::cout << "\tError: " << err.what() << '\n';
    }
    std::cout << "view.at(1): " << view.at(1) << '\n';
    try {
        std::cout << "view.at(10): " << view.at(10) << '\n';
    } catch (const std::out_of_range& err) {
        std::cout << "\tError: " << err.what() << '\n';
    }
    return 0;
}
