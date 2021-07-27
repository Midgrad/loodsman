
#ifndef TYPES_DEFINES_H
#define TYPES_DEFINES_H

#include <string>
#include <list>

//TODO: parametrize in cmake
namespace
{
const int MAX_PACKET_LENGTH = 500; //Presumably, max length of the atomic send/receive in a ordinary network
const int MAX_MTU = 1500;
} // namespace

namespace loodsman
{

using byte_t = char;
using bytearray_t = std::basic_string<byte_t>;
using string_list_t = std::list<std::string>;

}

#endif