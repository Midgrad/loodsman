#ifndef I_LINK_H
#define I_LINK_H

#include "types.h"
#include <boost/asio.hpp>

namespace loodsman
{

class ILink
{
public:
    virtual ~ILink() = default;
 
    virtual std::size_t send(const bytearray_t& data) = 0;
    virtual bytearray_t receive() = 0;

    virtual int open() = 0;
    virtual int close() = 0;

protected:
    boost::asio::io_context m_io;

};

using link_ptr = std::shared_ptr<ILink>;

} // namespace loodsman
#endif //I_LINK_H