#include <cstddef>
#include <iostream>

namespace my {
class string {
  private:
    char* ptr_{};
    std::size_t capacity_{};
    std::size_t size_{};

  public:
    explicit string(const char* prompt) {
        std::size_t len{};
        while (prompt[len] != '\0') {
            ++len;
        }
        size_ = len;
        ptr_ = new char[len + 1];
        capacity_ = len;
        for (std::size_t i{0}; i < size_; ++i) {
            ptr_[i] = prompt[i];
        }
        ptr_[len] = '\0';
    }
    ~string() { delete[] ptr_; }
    string() = default;
    [[nodiscard]] std::size_t capacity() const { return capacity_; }
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] const char* c_str() const {
        if (ptr_ == nullptr) {
            return "";
        }
        return ptr_;
    }
    char& operator[](std::size_t index) { return ptr_[index]; }
    const char& operator[](std::size_t index) const { return ptr_[index]; }
};
} // namespace my

int main() {
    my::string str{"hello"};

    std::cout << "====== TESTS ======" << '\n';
    std::cout << "old str.c_str(): " << str.c_str() << '\n';
    std::cout << "old str[1]:      " << str[1] << '\n';
    str[1] = 'a';
    std::cout << "new str[1]:      " << str[1] << '\n';
    std::cout << "new str.c_str(): " << str.c_str() << '\n';
    std::cout << "====== TESTS ======" << '\n';

    return 0;
}
