#ifndef I_LINK_H
#define I_LINK_H

#include "types.h"
#include <boost/asio.hpp>

using namespace boost::asio;

//TODO: parametrize this sizes and remove mavlink ref
namespace
{
const int MAX_PACKET_LENGTH = 300; // mavlink v2 279 bytes + overhead
const int MAX_MTU = 1500;
} // namespace

namespace loodsman
{

class ILink
{
public:
    virtual ~ILink() = default;
    virtual int send(const bytearray_t& data) = 0;
    virtual bytearray_t receive() = 0;

    virtual void open() = 0;
    virtual void close() = 0;

protected:
    io_context m_io;

};

} // namespace loodsman
#endif //I_LINK_H