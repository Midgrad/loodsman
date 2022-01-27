#include "link_factory.h"

#include "udp_link.h"
#include "utils.h"

#include <string_view>

using namespace loodsman;

LinkFactory::LinkFactory() : m_errorCode()
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
            // TODO: sync error codes with boost::system::system_error
            //            m_errorCode = boost::system::error_code();
            break;
        case LinkType::serial:
            utils::debugPrint("Serial Link type is not implemented");
            // TODO: sync error codes with boost::system::system_error
            //            m_errorCode = boost::system::error_code();
            break;
        default:
            //            m_errorCode = boost::system::error_code();
            utils::debugPrint("Unknown link type");
        }
    }
    catch (const boost::system::system_error& error)
    {
        utils::debugPrint("boost system error");
        m_errorCode = error.code();
        utils::debugPrint(error.code().message());
    }
    catch (...)
    {
        utils::debugPrint("Generic error");
        // TODO: sync error codes with boost::system::system_error
        //            m_errorCode = boost::system::error_code();
    }

    return link;
}

std::string LinkFactory::errorMessage() const
{
    return m_errorCode.message();
}

int LinkFactory::errorCode() const
{
    return m_errorCode.value();
}
