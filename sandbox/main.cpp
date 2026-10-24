#include <cstddef>
#include <iostream>

namespace my {
class string {
  private:
    char* ptr_{};
    std::size_t capacity_{};
    std::size_t size_{};

  public:
    ~string() { delete[] ptr_; }
    [[nodiscard]] std::size_t capacity() const { return capacity_; }
    [[nodiscard]] std::size_t size() const { return size_; }
};
} // namespace my

int main() {
    my::string str{};
    std::cout << str.size() << ' ';
    std::cout << str.capacity() << ' ';
    return 0;
}
