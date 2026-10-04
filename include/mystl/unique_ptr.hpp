#pragma once

namespace my {
template <typename T> class unique_ptr {
  private:
    T* ptr_;

  public:
    explicit unique_ptr(T* p) : ptr_(p) {}
    ~unique_ptr() { delete ptr_; }
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }
    void reset(T* p = nullptr) {
        delete ptr_;
        ptr_ = p;
    }
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
};
} // namespace my
