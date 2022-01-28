#include "link_factory.h"

#include "udp_link.h"
#include "utils.h"

#include <boost/system/error_code.hpp>
#include <string_view>

using namespace loodsman;

LinkAsync* LinkFactory::create(const LinkType type, const int localPort,
                               const std::string& localAddress, const int remotePort,
                               const std::string& remoteAddress) noexcept
{
    LinkAsync* link = nullptr;

    if ((localPort < 0) || (remotePort < 0))
    {
        utils::debugPrint("LinkFactory: port number could not be negative!");
        m_errorCode = boost::system::errc::make_error_code(boost::system::errc::invalid_argument);
        return nullptr;
    }

    try
    {
        switch (type)
        {
        case LinkType::udp:
            link = new UdpLink(localPort, localAddress, remotePort, remoteAddress);
            break;
        case LinkType::tcp:
            utils::debugPrint("TCP Link type is not implemented");
            m_errorCode = boost::system::errc::make_error_code(boost::system::errc::not_supported);
            break;
        case LinkType::serial:
            utils::debugPrint("Serial Link type is not implemented");
            m_errorCode = boost::system::errc::make_error_code(boost::system::errc::not_supported);
            break;
        default:
            m_errorCode = boost::system::errc::make_error_code(boost::system::errc::not_supported);
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
        m_errorCode = boost::system::errc::make_error_code(boost::system::errc::not_supported);
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
