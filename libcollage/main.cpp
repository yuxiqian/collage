#include "libcollage.h"
#include <iostream>

using LibCollage::compare;

int main() {
    std::cout << compare("utf8", "你好", "世界") << std::endl;
    std::cout << compare("utf8", "A", "B") << std::endl;
    std::cout << compare("utf8", "A", "A") << std::endl;
    std::cout << compare("ucs2_icelandic_ci", "A", "A") << std::endl;
    std::cout << compare("not a valid charset", "A", "A") << std::endl;
}