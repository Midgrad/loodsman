
#ifndef TYPES_DEFINES_H
#define TYPES_DEFINES_H

#include <string>
#include <list>

namespace loodsman
{

using byte_t = char;
using bytearray_t = std::basic_string<byte_t>;
using string_list_t = std::list<std::string>;

// using udp::endpoint = boost::asio::ip::udp::endpoint;

}

#endif