#include <cstddef>
#include <utility>

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
    string(const string& other) { *this = other; }
    string& operator=(const string& other) {
        if (this == &other) {
            return *this;
        }
        delete[] ptr_;
        size_ = other.size();
        ptr_ = new char[other.size() + 1];
        capacity_ = size_;
        for (std::size_t i{0}; i < size_; ++i) {
            ptr_[i] = other[i];
        }
        ptr_[size_] = '\0';
        return *this;
    }
    string& operator=(string&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        size_ = other.size_;
        other.size_ = 0;
        capacity_ = other.capacity_;
        other.capacity_ = 0;
        return *this;
    }
    string(string&& other) noexcept { *this = std::move(other); }
};
} // namespace my

int main() {
    my::string a{"hello"};
    return 0;
}
