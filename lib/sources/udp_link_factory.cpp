#include "udp_link_factory.h"

#include "i_link.h"
#include "udp_link.h"
#include "utils.h"

#include <string_view>

using namespace loodsman;

UdpLinkFactory::UdpLinkFactory(int localPort, std::string_view localAddress, int remotePort,
                               std::string_view remoteAddress) :
    m_errorCode(0),
    m_localPort(localPort),
    m_localAddress(localAddress),
    m_remotePort(remotePort),
    m_remoteAddress(remoteAddress)
{
}

UdpLinkFactory::UdpLinkFactory(int localPort, std::string_view localAddress) :
    UdpLinkFactory(localPort, localAddress, 0, "0.0.0.0")
{
}

UdpLinkFactory::UdpLinkFactory(int localPort) : UdpLinkFactory(localPort, "0.0.0.0", 0, "0.0.0.0")
{
}

ILink* UdpLinkFactory::create()
{
    ILink* link = nullptr;

    try
    {
        link = new UdpLink(m_localPort, m_localAddress, m_remotePort, m_remoteAddress);
    }
    catch (const boost::system::system_error& error)
    {
        debugPrint("boost system error");
        m_errorCode = error.code().value();
        std::cout << error.code().message();
    }
    catch (...)
    {
        debugPrint("Generic error");
        m_errorCode = 1;
    }

    return link;
}
int UdpLinkFactory::errorCode() const
{
    return m_errorCode;
}
