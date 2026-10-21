#pragma once

#include <cstddef>
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
        if (other.count_ == nullptr) {
            return;
        }
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
        if (count_ != nullptr) {
            ++count_->owners;
        }
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

    void release() {
        if (count_ == nullptr) {
            return;
        }
        --count_->tracking;
        if (count_->tracking == 0 && count_->owners == 0) {
            delete count_;
        }
    }

  public:
    explicit weak_ptr(const shared_ptr<T>& w) : ptr_{w.ptr_}, count_{w.count_} {
        if (w.count_ == nullptr) {
            return;
        }
        ++count_->tracking;
    }
    weak_ptr() = default;
    ~weak_ptr() { release(); }
    [[nodiscard]] bool expired() const { return count_ == nullptr || count_->owners == 0; }
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
    weak_ptr(const weak_ptr& other) : ptr_(other.ptr_), count_(other.count_) {
        if (other.count_ == nullptr) {
            return;
        }
        ++count_->tracking;
    }
    weak_ptr& operator=(const weak_ptr& other) {
        if (this == &other) {
            return *this;
        }
        release();
        ptr_ = other.ptr_;
        count_ = other.count_;
        if (count_ != nullptr) {
            ++count_->tracking;
        }
        return *this;
    }
    weak_ptr(weak_ptr&& other) noexcept { *this = std::move(other); }
    weak_ptr& operator=(weak_ptr&& other) noexcept {
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
    [[nodiscard]] std::size_t use_count() const {
        if (count_ == nullptr) {
            return 0;
        }
        return count_->owners;
    }
};
} // namespace my
