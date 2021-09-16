#include "udp_link.h"

#include "utils.h"

#include <iostream>

using namespace loodsman;
using namespace boost::asio;
using std::string;
using std::string_view;
using namespace std::placeholders;

UdpLink::UdpLink(boost::asio::io_context& ioContext, int localPort, const string& localAddress,
                 int remotePort, const string& remoteAddress) :
    m_socket(ioContext, ip::udp::endpoint(ip::make_address(localAddress), localPort)),
    m_buffer{}
{
    m_remoteEndpoint = ip::udp::endpoint(ip::make_address(remoteAddress), remotePort);
}

int UdpLink::open()
{
    boost::system::error_code error;
    m_socket.open(ip::udp::v4(), error);
    if (error.value())
        debugPrint(error.message());
    return error.value();
}

int UdpLink::close()
{
    boost::system::error_code error;
    m_socket.close();
    if (error.value())
        debugPrint(error.message());
    return error.value();
}

int UdpLink::bind(int port)
{
    boost::system::error_code error;
    m_socket.bind(ip::udp::endpoint(ip::udp::v4(), port), error);
    if (error.value())
        debugPrint(error.message());
    return error.value();
}

// Presumably used to permanently bind socket to a remote address, and prevent changes.
// may be helpful if we would use immutable objects
int UdpLink::connect(const string& remoteAddress, int remotePort)
{
    boost::system::error_code error;
    m_socket.connect(ip::udp::endpoint(ip::make_address(remoteAddress), remotePort), error);
    if (error.value())
        debugPrint(error.message());
    return error.value();
}

string UdpLink::localAddress() const
{
    return m_socket.local_endpoint().address().to_string();
}

int UdpLink::localPort() const
{
    return m_socket.local_endpoint().port();
}

string UdpLink::errorMessage() const
{
    return m_errorCode.message();
}

int UdpLink::errorCode() const
{
    return m_errorCode.value();
}

string UdpLink::remoteAddress() const
{
    return m_remoteEndpoint.address().to_string();
}

int UdpLink::remotePort() const
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