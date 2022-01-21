#include "link_factory.h"

#include "i_link.h"
#include "udp_link.h"
#include "utils.h"

#include <iostream>
#include <string_view>

using namespace loodsman;

LinkFactory::LinkFactory() : m_errorCode(0)
{
}

LinkAsync* LinkFactory::create(LinkType type, int localPort, const std::string& localAddress,
                               int remotePort, const std::string& remoteAddress)
{
    LinkAsync* link = nullptr;

    try
    {
        switch (type)
        {
        case LinkType::udp:
            link = new UdpLink(localPort, localAddress, remotePort, remoteAddress);
            break;
        case LinkType::tcp:
            std::cout << "TCP Link type is not implemented" << std::endl;
            // TODO: Fix magic number, sync error codes with boost::system::system_error
            m_errorCode = 1;
            break;
        case LinkType::serial:
            std::cout << "Serial Link type is not implemented" << std::endl;
            // TODO: Fix magic number, sync error codes with boost::system::system_error
            m_errorCode = 1;
            break;
        default:
            m_errorCode = 2;
            std::cout << "Unknown link type" << std::endl;
        }
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

int LinkFactory::errorCode() const
{
    return m_errorCode;
}
