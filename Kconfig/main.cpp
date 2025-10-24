#include <iostream>
#include "config.h"   // auto-generated from .config

int main() {
#if CONFIG_ENABLE_FEATURE
    std::cout << "Feature is ENABLED" << std::endl;
#else
    std::cout << "Feature is DISABLED" << std::endl;
#endif

    std::cout << "Max value: " << CONFIG_MAX_VALUE << std::endl;
    std::cout << "User name: " << CONFIG_NAME << std::endl;

    return 0;
}
