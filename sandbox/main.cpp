#include <iostream>
#include <mystl/vector.hpp>
#include <utility>

int main() {
    my::vector<int> a{1, 2, 3};
    my::vector<int> b = std::move(a);
    my::vector<int> c{7, 8};
    c = std::move(b);
    std::cout << "a.size(): " << a.size() << '\n';
    std::cout << "b.size(): " << b.size() << '\n';
    std::cout << "c.size(): " << c.size() << '\n';
    std::cout << "x: ";
    for (int x : c) {
        std::cout << x << ' ';
    }
    return 0;
}
