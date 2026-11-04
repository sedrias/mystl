#include <mystl/function.hpp>

int main() {
    my::function<int(int)> f;
    my::function<void()> a;
    my::function<double(int, char)> b;
    my::function<int(int, int, int, int)> c;
    return 0;
}
