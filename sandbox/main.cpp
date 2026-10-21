#include <mystl/shared_ptr.hpp>

int main() {
    my::shared_ptr<int> a{new int{5}};
    my::weak_ptr<int> b{a};
    return 0;
}
