#include <cstddef>
#include <iostream>
#include <utility>

namespace my {
struct control_block {
    std::size_t owners{0};
    std::size_t tracking{0};
};

template <typename T> class shared_ptr {
  private:
    T* ptr_{};
    control_block* count_{};

    void release() {
        if (count_ == nullptr) {
            return;
        }
        --count_->owners;
        if (count_->owners == 0) {
            delete ptr_;
        }
        if (count_->owners == 0 && count_->tracking == 0) {
            delete count_;
        }
    }

  public:
    explicit shared_ptr(T* s) : ptr_(s), count_{new control_block{1}} {}
    ~shared_ptr() { release(); }
    shared_ptr(const shared_ptr& other) : ptr_{other.ptr_}, count_{other.count_} {
        ++count_->owners;
    }
    [[nodiscard]] std::size_t use_count() const {
        if (count_ == nullptr) {
            return 0;
        }
        return count_->owners;
    }
    shared_ptr& operator=(const shared_ptr& other) {
        if (this == &other) {
            return *this;
        }
        release();
        ptr_ = other.ptr_;
        count_ = other.count_;
        ++count_->owners;
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
    T* get() const { return ptr_; }
    T* operator->() const { return ptr_; }
};
} // namespace my

int main() {
    my::shared_ptr<int> a{new int{5}};
    my::shared_ptr<int> b = a;
    std::cout << "a/b.use_count(): " << a.use_count() << ' ' << b.use_count() << '\n';
    my::shared_ptr<int> c{new int{}};
    c = a;
    std::cout << "a.use_count(): " << a.use_count() << '\n';
    return 0;
}
