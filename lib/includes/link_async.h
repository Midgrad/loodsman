#ifndef LINK_ASYNC_H
#define LINK_ASYNC_H

#include <boost/asio.hpp>

#include "i_link.h"

#include <functional>
#include <string_view>

namespace loodsman
{
using ReceiveHandler = std::function<void(std::string)>;
using SendHandler = std::function<void(std::size_t)>;

class LinkAsync : public ILink
{
public:
    LinkAsync() = default;

    virtual void asyncSend(std::string_view data, SendHandler handler) = 0;
    virtual void asyncReceive(ReceiveHandler) = 0;

    void checkHandlers();
    void runHandlers();

protected:
    boost::asio::io_context m_ioContext;
};

} // namespace loodsman
#endif //LINK_ASYNC_H
