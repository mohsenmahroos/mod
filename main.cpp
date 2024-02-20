#include "mod.hpp"

int main() {
    mod<1000000009> x, y;
    std::cin >> x >> y;
    std::cout << (x+y)();
    return 0; }
