#include "link_factory.h"

#include "i_link.h"
#include "udp_link.h"
#include "utils.h"

#include <string_view>
#include <iostream>

using namespace loodsman;

LinkFactory::LinkFactory() :
    //TODO: for testing purpose only - do not store context here!
    m_ioContext(),
    m_errorCode(0)
{
}

ILinkAsync* LinkFactory::create(LinkType type, int localPort, const std::string& localAddress, int remotePort,
                                   const std::string& remoteAddress)
{
    ILinkAsync* link = nullptr;

    try
    {
        switch (type)
        {
        case LinkType::udp:
            link = new UdpLink(m_ioContext, localPort, localAddress, remotePort, remoteAddress);
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

void LinkFactory::checkHandlers()
{
    m_ioContext.poll();
    m_ioContext.reset();
}