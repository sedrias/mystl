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
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range{"pop_back() size_ is empty"};
        }
        --size_;
    }
    [[nodiscard]] bool empty() const { return size_ == 0; }
    void clear() { size_ = 0; }
};
} // namespace my

int main() {
    my::vector<int> v{};
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << "v.size(): " << v.size() << '\n';
    std::cout << "v.empty(): " << v.empty() << '\n';
    v.clear();
    std::cout << "v.size(): " << v.size() << '\n';
    std::cout << "v.empty(): " << v.empty() << '\n';
    return 0;
}
