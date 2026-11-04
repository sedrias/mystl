#pragma once

namespace my {
template <typename Signature> class function;
template <typename R, typename... Args> class function<R(Args...)> {
  private:
    struct Base {
        virtual R call(Args... args) = 0;
        virtual ~Base() = default;
    };
    template <typename F> struct Holder : Base {
        F f_;
        Holder(F f) : f_(f) {}
        R call(Args... args) override { return f_(args...); }
    };
    Base* p_{};

  public:
    template <typename F> function(F f) { p_ = new Holder<F>(f); }
    ~function() { delete p_; }
    R operator()(Args... args) { return p_->call(args...); }
};
} // namespace my
