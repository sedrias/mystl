#include <cstddef>
#include <iostream>

namespace my {
template <typename T> class shared_ptr {
  private:
    T* ptr_{};
    std::size_t* count_{};

  public:
    explicit shared_ptr(T* s) : ptr_(s), count_{new std::size_t{1}} {}
    ~shared_ptr() {
        --*count_;
        if (*count_ == 0) {
            delete ptr_;
            delete count_;
        }
    }
    shared_ptr(const shared_ptr& other) : ptr_{other.ptr_}, count_{other.count_} { ++*count_; }
    [[nodiscard]] std::size_t use_count() const { return *count_; }
};
} // namespace my

int main() {
    my::shared_ptr<int> a{new int{1}};
    my::shared_ptr<int> b = a;
    std::cout << a.use_count() << ' ' << b.use_count();
    return 0;
}
