#include "UdpLinkFactory.h"
#include "ILinkFactory.h"
#include "i_link.h"
#include "udp_link.h"
#include "utils.h"
#include <string_view>

using namespace loodsman;

UdpLinkFactory::UdpLinkFactory(int local_port) :
    m_local_port(local_port),
    m_local_address("0.0.0.0"),
    m_remote_port(0),
    m_remote_address("0.0.0.0")
{
}

UdpLinkFactory::UdpLinkFactory(int local_port, std::string local_address) :
    m_local_port(local_port),
    m_local_address(local_address),
    m_remote_port(0),
    m_remote_address("0.0.0.0")
{
}

UdpLinkFactory::UdpLinkFactory(int local_port, std::string local_address, int remote_port,
                               std::string remote_address) :
    m_local_port(local_port),
    m_local_address(local_address),
    m_remote_port(remote_port),
    m_remote_address(remote_address)
{
}

int UdpLinkFactory::create(ILink* link)
{
    try
    {
        UdpLink(m_local_port, m_local_address, m_remote_port, m_remote_address);
    }
    catch (const boost::system::system_error& error)
    {
        debug_print("boost system error");
        return -1;
    }
    catch (...)
    {
        debug_print("Generic error");
        return -1;
    }

    return 0;
}
