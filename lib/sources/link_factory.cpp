#include "link_factory.h"

#include "udp_link.h"
#include "utils.h"

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
            utils::debugPrint("TCP Link type is not implemented");
            // TODO: Fix magic number, sync error codes with boost::system::system_error
            m_errorCode = 1;
            break;
        case LinkType::serial:
            utils::debugPrint("Serial Link type is not implemented");
            // TODO: Fix magic number, sync error codes with boost::system::system_error
            m_errorCode = 1;
            break;
        default:
            m_errorCode = 2;
            utils::debugPrint("Unknown link type");
        }
    }
    catch (const boost::system::system_error& error)
    {
        utils::debugPrint("boost system error");
        m_errorCode = error.code().value();
        utils::debugPrint(error.code().message());
    }
    catch (...)
    {
        utils::debugPrint("Generic error");
        m_errorCode = 1;
    }

    return link;
}

int LinkFactory::errorCode() const
{
    return m_errorCode;
}
