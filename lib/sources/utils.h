#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string_view>

namespace utils
{
inline void debugPrint(std::string_view message)
{
#ifdef VERBOSE_OUTPUT
    std::cout << message << std::endl;
#endif
}
} // namespace utils

#endif //UTILS_H
