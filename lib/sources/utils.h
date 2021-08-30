
#ifndef LOODSMAN_UTILS_H
#define LOODSMAN_UTILS_H

#include <iostream>

//TODO: parametrize in cmake and split into several files
namespace
{
void debug_print(std::string_view message)
{
    if (DEBUG_VERBOSITY)
        std::cout << message << std::endl;
}

} // namespace

#endif
