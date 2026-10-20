#include <cstddef>
#include <iostream>
#include <utility>

namespace my {
struct control_block {
    std::size_t owners{0};
    std::size_t tracking{0};
};

template <typename T> class weak_ptr;

template <typename T> class shared_ptr {
    template <typename U> friend class weak_ptr;

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
    shared_ptr() = default;
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

template <typename T> class weak_ptr {
  private:
    T* ptr_{};
    control_block* count_{};

  public:
    explicit weak_ptr(const shared_ptr<T>& w) : ptr_{w.ptr_}, count_{w.count_} {
        ++count_->tracking;
    }
    ~weak_ptr() {
        --count_->tracking;
        if (count_->tracking == 0 && count_->owners == 0) {
            delete count_;
        }
    }
    [[nodiscard]] bool expired() const { return count_->owners == 0; }
    [[nodiscard]] shared_ptr<T> lock() const {
        if (expired()) {
            return shared_ptr<T>{};
        }
        shared_ptr<T> result;
        result.ptr_ = ptr_;
        result.count_ = count_;
        ++count_->owners;
        return result;
    }
};
} // namespace my

int main() {
    my::shared_ptr<int> s{new int{9}};
    my::weak_ptr<int> w{s};
    {
        my::shared_ptr<int> p{w.lock()};
        my::shared_ptr<int> tmp{std::move(s)};
    }
    my::shared_ptr<int> sp{w.lock()};
    std::cout << "sp.use_count(): " << sp.use_count() << '\n';
    return 0;
}
