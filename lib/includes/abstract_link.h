#ifndef ABSTRACT_LINK_H
#define ABSTRACT_LINK_H

#include "types.h"
#include <boost/asio.hpp>

//TODO: parametrize this sizes and remove mavlink ref
namespace
{
const int MAX_PACKET_LENGTH = 300; // mavlink v2 279 bytes + overhead
const int MAX_MTU = 1500;
} // namespace

namespace loodsman
{
enum class link_type
{
    UDP,
    TCP,
    SERIAL
};

class AbstractLink
{
public:
    virtual ~AbstractLink() = default;
    virtual int send(const bytearray_t& data) = 0;
    virtual bytearray_t receive() = 0;

protected:
    boost::asio::io_context m_io;

};

using link_ptr = std::shared_ptr<loodsman::AbstractLink>;

} // namespace loodsman
#endif // ABSTRACT_LINK_H