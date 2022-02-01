#include "udp_link.h"

#include "utils.h"

#include <iostream>

using namespace loodsman;
using namespace boost::asio;
using std::string;
using std::string_view;
using namespace std::placeholders;

UdpLink::UdpLink(unsigned int localPort, const string& localAddress, unsigned int remotePort,
                 const string& remoteAddress) :
    m_remoteEndpoint(ip::udp::endpoint(ip::make_address(remoteAddress),
                                       static_cast<unsigned short>(remotePort))),
    m_localEndpoint(
        ip::udp::endpoint(ip::make_address(localAddress), static_cast<unsigned short>(localPort))),
    m_socket(m_ioContext, ip::udp::endpoint(ip::make_address(localAddress),
                                            static_cast<unsigned short>(localPort)))
{
}

std::error_code UdpLink::open()
{
    m_socket.open(ip::udp::v4(), m_errorCode);
    if (m_errorCode.value())
    {
        utils::debugPrint(m_errorCode.message());
    }

    m_errorCode = this->bind();
    if (m_errorCode.value())
    {
        utils::debugPrint(m_errorCode.message());
    }

    return static_cast<std::error_code>(m_errorCode);
}

void UdpLink::close()
{
    m_socket.close();
}

boost::system::error_code UdpLink::bind()
{
    m_errorCode = m_socket.bind(m_localEndpoint, m_errorCode);
    if (m_errorCode.value())
        utils::debugPrint(m_errorCode.message());
    return m_errorCode;
}

// Presumably used to permanently bind socket to a remote address, and prevent changes.
// may be helpful if we would use immutable objects
boost::system::error_code UdpLink::connect()
{
    m_errorCode = m_socket.connect(m_remoteEndpoint, m_errorCode);
    if (m_errorCode.value())
        utils::debugPrint(m_errorCode.message());
    return m_errorCode;
}

[[maybe_unused]] string UdpLink::localAddress() const
{
    return m_localEndpoint.address().to_string();
}

[[maybe_unused]] int UdpLink::localPort() const
{
    return m_localEndpoint.port();
}

string UdpLink::errorMessage() const
{
    return m_errorCode.message();
}

int UdpLink::errorCode() const
{
    return m_errorCode.value();
}

[[maybe_unused]] string UdpLink::remoteAddress() const
{
    return m_remoteEndpoint.address().to_string();
}

[[maybe_unused]] int UdpLink::remotePort() const
{
    return m_remoteEndpoint.port();
}

std::string UdpLink::receive()
{
    std::size_t bytesTransferred = m_socket.receive_from(buffer(m_buffer), m_remoteEndpoint,
                                                         socket_base::message_flags(), m_errorCode);

    return { m_buffer, bytesTransferred };
}

std::size_t UdpLink::send(string_view data)
{
    std::size_t dataSize = data.size();
    std::size_t bytesTransferred = m_socket.send_to(buffer(data, dataSize), m_remoteEndpoint,
                                                    socket_base::message_flags(), m_errorCode);
    return bytesTransferred;
}

void UdpLink::asyncReceive(ReceiveHandler handler)
{
    m_socket.async_receive_from(buffer(m_buffer), m_remoteEndpoint, socket_base::message_flags(),
                                std::bind(loodsman::UdpLink::asyncReceiveHandlerWrapper, _1, _2,
                                          this, handler));
}

void UdpLink::asyncSend(std::string_view data, SendHandler handler)
{
    std::size_t dataSize = data.size();
    if (dataSize > LOODSMAN_MAX_PACKET_LENGTH)
        utils::debugPrint("Message that are trying to be send is too big, truncating!");
    m_socket.async_send_to(buffer(data, dataSize), m_remoteEndpoint, socket_base::message_flags(),
                           std::bind(loodsman::UdpLink::asyncSendHandlerWrapper, _1, _2, this,
                                     handler));
}

void UdpLink::asyncReceiveHandlerWrapper(const boost::system::error_code& errorCode,
                                         std::size_t bytesTransferred, UdpLink* link,
                                         const ReceiveHandler& handler)
{
    link->m_errorCode = errorCode;
    std::string data = { link->m_buffer, bytesTransferred };
    handler(data);
}

void UdpLink::asyncSendHandlerWrapper(const boost::system::error_code& errorCode,
                                      std::size_t bytesTransferred, UdpLink* link,
                                      const SendHandler& handler)
{
    link->m_errorCode = errorCode;
    handler(bytesTransferred);
}