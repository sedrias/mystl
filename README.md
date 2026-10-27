# mystl

Educational implementations of C++ standard library components.
A C++23 header-only library.

## Done

- `my::unique_ptr` - smart pointer with exclusive ownership: move-only, supports `get`, `*`, `->`, `release` and `reset`
- `my::vector` - dynamic array: `push_back`, `pop_back`, `[]`, `at()`, `reserve`, `begin`/`end`, initializer list, copy and move
- `my::shared_ptr` and `my::weak_ptr` - reference-counted smart pointers: shared ownership with `use_count`, `*` and `->`, and a non-owning observer with `expired` and `lock`; copy and move
- `my::string` - string class with small string optimization (SSO): `push_back`, `[]`, `reserve`, `c_str`, copy and move

## Planned

- `hash_map` - hash table
- `function` - type-erased callable wrapper

## Usage

Include a header from `include/mystl/`:

### unique_ptr

```cpp
#include <mystl/unique_ptr.hpp>
#include <utility> // needed for std::move

my::unique_ptr<int> p{new int{42}};
my::unique_ptr<int> q = std::move(p);
```

### vector

```cpp
#include <mystl/vector.hpp>

my::vector<int> v{1, 2, 3};
v.push_back(4);
```

### shared_ptr + weak_ptr

```cpp
#include <mystl/shared_ptr.hpp>

my::shared_ptr<int> s{new int{5}};
my::weak_ptr<int> w{s};

if (!w.expired()) {
    auto p = w.lock();
}
```

### string

```cpp
#include <mystl/string.hpp>
#include <iostream> // needed for std::cout

my::string s{"hello"}; // hello
s.push_back('!'); 
std::cout << s.c_str() << '\n'; // hello!
```

## Build

```bash
cmake --preset debug
cmake --build build/debug
```
