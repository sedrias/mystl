# mystl

Educational implementations of C++ standard library components.
A C++23 header-only library.

## Done

- `my::unique_ptr` - smart pointer with exclusive ownership: move-only, supports `get`, `*`, `->`, `release` and `reset`
- `my::vector` - dynamic array: `push_back`, `pop_back`, `[]`, `at()`, `reserve`, `begin`/`end`, initializer list, copy and move

## In progress

- `shared_ptr` - implemented, but still in `sandbox/main.cpp` and not moved to a header yet
- `weak_ptr` - already implemented, copy and move are missing

## Planned

- `string` - string class with small string optimization (SSO)
- `hash_map` - hash table
- `function` - type-erased callable wrapper

## Usage

Include a header from `include/mystl/`

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

## Build

```bash
cmake --preset debug
cmake --build build/debug
```
