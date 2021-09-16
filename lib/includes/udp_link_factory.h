#ifndef UDP_LINK_FACTORY_H
#define UDP_LINK_FACTORY_H

#include "i_link_factory.h"

#include "i_link.h"

#include <string>
#include <string_view>

#include <boost/asio.hpp>

namespace loodsman
{
class UdpLinkFactory : public ILinkFactory
{
public:
    UdpLinkFactory(int localPort, std::string_view localAddress, int remotePort,
                   std::string_view remoteAddress);

    UdpLinkFactory(int localPort, std::string_view localAddress);

    UdpLinkFactory(int localPort);

    ILink* create() override;

    int errorCode() const override;

private:
    //TODO: for testing purpose only - do not store context here!

    boost::asio::io_context m_ioContext;
    const int m_localPort;
    const std::string m_localAddress;
    const int m_remotePort;
    const std::string m_remoteAddress;
    int m_errorCode;

public:
};
} // namespace loodsman
#endif //UDP_LINK_FACTORY_H
