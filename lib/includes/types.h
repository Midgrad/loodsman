
#ifndef TYPES_DEFINES_H
#define TYPES_DEFINES_H

#include <vector>
#include <iostream>

//TODO: parametrize in cmake and split into several files
namespace
{
const int MAX_PACKET_LENGTH = 500; //Presumably, max length of the atomic send/receive in a ordinary network
const int MAX_MTU = 1500;
const int DEBUG_VERBOSITY = 1;

void debug_print(const std::string& message)
{
    if (DEBUG_VERBOSITY) std::cout << message << std::endl;
}

} // namespace

//TODO: discuss moving to nameless namespace

namespace loodsman
{

enum class link_type
{
    udp,
    tcp,
    serial
};

using bytearray_t = std::basic_string<char>;

}

#endif