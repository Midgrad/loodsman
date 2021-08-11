#include "udp_link.h"
#include "utils.h"
#include <iostream>

using namespace loodsman;
using namespace boost::asio;
using std::string;
using std::string_view;

UdpLink::UdpLink(int local_port,const string& local_address, int remote_port, const string& remote_address):
m_socket(m_io,ip::udp::endpoint(ip::make_address(local_address), local_port)), m_buffer{}
{
    m_remote_endpoint = ip::udp::endpoint(ip::make_address(remote_address), remote_port);
}

int UdpLink::open()
{
    boost::system::error_code error;
    m_socket.open(ip::udp::v4(), error);
    if(error.value()) debug_print(error.message());
    return error.value();
}

int UdpLink::close()
{
    boost::system::error_code error;        
    m_socket.close();
    if(error.value()) debug_print(error.message());
    return error.value();
}

int UdpLink::bind(int port)
{
    boost::system::error_code error;
    m_socket.bind(ip::udp::endpoint(ip::udp::v4(), port), error);
    if(error.value()) debug_print(error.message());
    return error.value();
}

// Presumably used to permanently bind socket to a remote address, and prevent changes. 
// may be helpful if we would use immutable objects
int UdpLink::connect(const string& address, int port)
{
    boost::system::error_code error;
    m_socket.connect(ip::udp::endpoint(ip::make_address(address), port), error);
    if(error.value()) debug_print(error.message());
    return error.value();
}

string UdpLink::localAddress() const
{
    return m_socket.local_endpoint().address().to_string();
}

uint UdpLink::localPort() const
{
    return m_socket.local_endpoint().port();
}

string UdpLink::errorMessage() const
{
    return m_errorCode.message();
}

uint UdpLink::errorCode() const
{
    return m_errorCode.value();
}

string UdpLink::remoteAddress() const
{
    return m_remote_endpoint.address().to_string();
}

uint UdpLink::remotePort() const
{
    return m_remote_endpoint.port();
}

string_view UdpLink::receive()
{
    std::size_t bytes_transferred = m_socket.receive_from(buffer(m_buffer), m_remote_endpoint, socket_base::message_flags(), m_errorCode);

    return string_view(m_buffer,bytes_transferred);
}

std::size_t UdpLink::send(string_view data)
{
    std::size_t data_size = data.size();
    std::size_t bytes_transferred = m_socket.send_to(buffer(data, data_size), m_remote_endpoint, socket_base::message_flags(), m_errorCode);
    return bytes_transferred;
}
