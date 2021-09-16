#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#include <functional>

#include <boost/asio.hpp>

//TODO: parametrize in cmake and split into several files
namespace
{
void debugPrint(std::string_view message)
{
    if (DEBUG_VERBOSITY)
        std::cout << message << std::endl;
}

} // namespace

#endif //UTILS_H
