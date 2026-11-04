#pragma once

namespace my {
template <typename Signature> class function;
template <typename R, typename... Args> class function<R(Args...)> {
  private:
    struct Base {
        virtual R call(Args... args) = 0;
        virtual ~Base() = default;
        virtual Base* clone() const = 0;
    };
    template <typename F> struct Holder : Base {
        F f_;
        Holder(F f) : f_(f) {}
        R call(Args... args) override { return f_(args...); }
        Base* clone() const override { return new Holder<F>(f_); }
    };
    Base* p_{};

  public:
    template <typename F> function(F f) { p_ = new Holder<F>(f); }
    ~function() { delete p_; }
    R operator()(Args... args) { return p_->call(args...); }
    function(const function& other) {
        if (other.p_ != nullptr) {
            p_ = other.p_->clone();
        }
    }
    function& operator=(const function& other) {
        if (this == &other) {
            return *this;
        }
        delete p_;
        p_ = nullptr;
        if (other.p_ != nullptr) {
            p_ = other.p_->clone();
        }
        return *this;
    }
    function(function&& other) noexcept {
        p_ = other.p_;
        other.p_ = nullptr;
    }
    function& operator=(function&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete p_;
        p_ = other.p_;
        other.p_ = nullptr;
        return *this;
    }
};
} // namespace my
