#pragma once

namespace my {
template <typename Signature> class function;
template <typename R, typename... Args> class function<R(Args...)> {};
} // namespace my
