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
        }
    }
};
} // namespace my

int main() {
    my::vector<int> test{};
    std::cout << test.size() << '\n';
    std::cout << test.capacity() << '\n';
    return 0;
}
