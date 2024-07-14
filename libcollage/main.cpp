#include "libcollage.h"
#include <iostream>

using LibCollage::compare;

int main() {
    std::cout << compare("gbk_chinese_ci", "A", "B") << std::endl;
    std::cout << compare("latin1_general_cs", "A", "a") << std::endl;
    std::cout << compare("latin1_general_ci", "A", "a") << std::endl;
    std::cout << compare("ucs2_icelandic_ci", "A", "A") << std::endl;
    std::cout << compare("not a valid charset", "A", "A") << std::endl;
}
