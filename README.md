# mystl

Educational implementations of C++ standard library components.
A C++23 header-only library.

## Done

- `my::unique_ptr` - smart pointer with exclusive ownership: move-only, supports `get`, `*`, `->`, `release` and `reset`
- `my::vector` - dynamic array: `push_back`, `pop_back`, `[]`, `at()`, `reserve`, `begin`/`end`, initializer list, copy and move
- `my::shared_ptr` and `my::weak_ptr` - reference-counted smart pointers: shared ownership with `use_count`, `*` and `->`, and a non-owning observer with `expired` and `lock`; copy and move
- `my::string` - string class with small string optimization (SSO): `push_back`, `[]`, `reserve`, `c_str`, copy and move
- `my::hash_map` - hash table that stores key-value pairs and finds a value by its key quickly, without scanning: `insert`, `find`, `erase`, `size`, `empty`; copy and move

## In progress

- `my::function` - a box that can hold a lambda, a regular function or any other callable, and call it the same way

## Usage

Include a header from `include/mystl/`:

### unique_ptr

```cpp
#include <mystl/unique_ptr.hpp>

int main() {
    my::unique_ptr<int> u{new int{42}};
    u.get();
    delete u.release();
    u.reset(new int{7});
    u.reset();
    return 0;
}
```

### vector

```cpp
#include <mystl/vector.hpp>

int main() {
    my::vector<int> v{1, 2, 3};
    v.push_back(4);
    v.pop_back();
    v.at(0);
    v.size();
    v.capacity();
    v.empty();
    v.reserve(10);
    v.begin();
    v.end();
    v.clear();
    return 0;
}
```

### shared_ptr + weak_ptr

```cpp
#include <mystl/shared_ptr.hpp>

int main() {
    my::shared_ptr<int> s{new int{5}};
    my::weak_ptr<int> w{s};
    s.use_count();
    s.get();
    w.expired();
    w.lock();
    w.use_count();
    return 0;
}
```

### string

```cpp
#include <mystl/string.hpp>

int main() {
    my::string s{"hello"};
    s.push_back('!');
    s.size();
    s.capacity();
    s.reserve(30);
    s.c_str();
    return 0;
}
```

### hash_map

```cpp
#include <mystl/hash_map.hpp>

int main() {
    my::hash_map<int, int> h;
    h.insert(1, 10);
    h.find(1);
    h.erase(1);
    h.size();
    h.empty();
    return 0;
}
```

## Build

```bash
cmake --preset debug
cmake --build build/debug
```
