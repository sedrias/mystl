#include <cstddef>
#include <iostream>

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
};
} // namespace my

int main() {
    my::vector<int> test{};
    test.push_back(10);
    std::cout << test.size() << '\t' << test.capacity() << '\n';
    test.push_back(10);
    std::cout << test.size() << '\t' << test.capacity() << '\n';
    test.push_back(10);
    std::cout << test.size() << '\t' << test.capacity() << '\n';
    test.push_back(10);
    std::cout << test.size() << '\t' << test.capacity() << '\n';
    test.push_back(10);
    std::cout << test.size() << '\t' << test.capacity() << '\n';
    return 0;
}
