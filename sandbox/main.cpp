#include <cstddef>
#include <iostream>
#include <utility>

namespace my {
template <typename T> class shared_ptr {
  private:
    T* ptr_{};
    std::size_t* count_{};

    void release() {
        if (count_ == nullptr) {
            return;
        }
        --*count_;
        if (*count_ == 0) {
            delete ptr_;
            delete count_;
        }
    }

  public:
    explicit shared_ptr(T* s) : ptr_(s), count_{new std::size_t{1}} {}
    ~shared_ptr() { release(); }
    shared_ptr(const shared_ptr& other) : ptr_{other.ptr_}, count_{other.count_} { ++*count_; }
    [[nodiscard]] std::size_t use_count() const {
        if (count_ == nullptr) {
            return 0;
        }
        return *count_;
    }
    shared_ptr& operator=(const shared_ptr& other) {
        if (this == &other) {
            return *this;
        }
        release();
        ptr_ = other.ptr_;
        count_ = other.count_;
        ++*count_;
        return *this;
    }
    T& operator*() const { return *ptr_; }
    shared_ptr(shared_ptr&& other) noexcept { *this = std::move(other); }
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        release();
        ptr_ = other.ptr_;
        count_ = other.count_;
        other.ptr_ = nullptr;
        other.count_ = nullptr;
        return *this;
    }
};
} // namespace my

int main() {
    my::shared_ptr<int> a{new int{5}};
    my::shared_ptr<int> b{std::move(a)};
    std::cout << "*b: " << *b << '\n' << "b.use_count(): " << b.use_count() << '\n';
    std::cout << a.use_count();
    return 0;
}
