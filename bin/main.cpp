
#include <lib/number.h>
#include <iostream>

int main() {
    char a[609];
    char c[609];
    std::cin >> a >> c ;
    uint2022_t k = from_string(a);
    uint2022_t f = from_string(c);
    std::cout << k * f;




    return 0;
}
