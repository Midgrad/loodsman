#include "udp_link_factory.h"
#include "i_link.h"
#include "i_link_factory.h"
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
    m_errorCode(0),
    m_localPort(localPort),
    m_localAddress(localAddress),
    m_remotePort(0),
    m_remoteAddress("0.0.0.0")
{
}

UdpLinkFactory::UdpLinkFactory(int localPort) :
    m_errorCode(0),
    m_localPort(localPort),
    m_localAddress("0.0.0.0"),
    m_remotePort(0),
    m_remoteAddress("0.0.0.0")
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
        debug_print("boost system error");
        m_errorCode = error.code().value();
        std::cout << error.code().message();
    }
    catch (...)
    {
        debug_print("Generic error");
        m_errorCode = 1;
    }

    return link;
}
int UdpLinkFactory::errorCode() const
{
    return m_errorCode;
}
