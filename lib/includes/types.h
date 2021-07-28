
#ifndef TYPES_DEFINES_H
#define TYPES_DEFINES_H

#include <string>
#include <list>
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

//TODO: disuss moving to nameless namespace

namespace loodsman
{

enum class link_type
{
    udp,
    tcp,
    serial
};

using byte_t = char;
using bytearray_t = std::basic_string<byte_t>;
using string_list_t = std::list<std::string>;

}

#endif