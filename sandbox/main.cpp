#include "mystl/unique_ptr.hpp"
#include <iostream>
#include <utility>

struct Tracker {
    Tracker() { std::cout << "Tracker created\n"; }
    ~Tracker() { std::cout << "Tracker destroyed\n"; }
    void hello() { std::cout << "Hello from Tracker\n"; }
};

int main() {
    {
        my::unique_ptr<Tracker> a(new Tracker{});
        Tracker* raw = a.release();
        std::cout << a.get() << '\n';
        delete raw;
        my::unique_ptr<Tracker> b(new Tracker{});
        std::cout << "before reset\n";
        b.reset(new Tracker{});
        std::cout << "after reset\n";
    }
    std::cout << "after block\n";
}