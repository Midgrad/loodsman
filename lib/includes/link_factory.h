#ifndef LINK_FACTORY_H
#define LINK_FACTORY_H

#include "i_link_factory.h"

#include "i_link_async.h"

#include <string>
#include <string_view>

#include <boost/asio.hpp>

namespace loodsman
{

enum class LinkType
{
    udp,
    tcp,
    serial
};

class LinkFactory : public ILinkFactory
{
public:
    LinkFactory();

    ILinkAsync* create(LinkType type ,int localPort, const std::string& localAddress = "0.0.0.0",
                       int remotePort = 0, const std::string& remoteAddress = "0.0.0.0");

//    ILinkAsync* create(LinkType type ,int baudRate);

    int errorCode() const override;

    void checkHandlers();

private:
    //TODO: for testing purpose only - do not store context here!
    boost::asio::io_context m_ioContext;
    int m_errorCode;

public:
};
} // namespace loodsman
#endif //LINK_FACTORY_H
