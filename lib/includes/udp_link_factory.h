#include "i_link.h"
#include "i_link_factory.h"
#include <string_view>

#ifndef UDP_LINK_FACTORY_H
#define UDP_LINK_FACTORY_H

namespace loodsman
{
class UdpLinkFactory : public ILinkFactory
{
public:
    UdpLinkFactory(int localPort);

    UdpLinkFactory(int localPort, std::string_view localAddress);

    UdpLinkFactory(int localPort, std::string_view localAddress, int remotePort,
                   std::string_view remoteAddress);

    ILink* create() override;

    int errorCode() const override;

private:
    const int m_localPort;
    const std::string m_localAddress;
    const int m_remotePort;
    const std::string m_remoteAddress;
    int m_errorCode;

public:
};
} // namespace loodsman
#endif //UDP_LINK_FACTORY_H
