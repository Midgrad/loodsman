#include "udp_link.h"
#include <iostream>

using namespace loodsman;
using namespace boost::asio;

//TODO: #7 Constructor should not fail! Remove init from it
UdpLink::UdpLink(int local_port):
m_socket(m_io)
{
    int error_code = 0;

    error_code = open();
    error_code = bind(local_port);
}

UdpLink::UdpLink(const std::string& remote_address, int remote_port):
m_socket(m_io)
{
    int error_code = 0;

    error_code = open();
    m_remote_endpoint = ip::udp::endpoint(ip::make_address(remote_address), remote_port);
}

//TODO:: return to the default or write the proper one
UdpLink::~UdpLink()
{
    this->close();
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
int UdpLink::connect(const std::string& address, int port)
{
    boost::system::error_code error;
    m_socket.connect(ip::udp::endpoint(ip::make_address(address), port), error);
    if(error.value()) debug_print(error.message());
    return error.value();
}

std::string UdpLink::localAddress() const
{
    return m_socket.local_endpoint().address().to_string();
}

uint UdpLink::localPort() const
{
    return m_socket.local_endpoint().port();
}

std::string UdpLink::remoteAddress() const
{
    return m_remote_endpoint.address().to_string();
}

uint UdpLink::remotePort() const
{
    return m_remote_endpoint.port();
}

bytearray_t UdpLink::receive()
{
    std::size_t bytes_transferred = m_socket.receive_from(buffer(m_buffer), m_remote_endpoint);
    
    bytearray_t data;
    data.assign(m_buffer, bytes_transferred);
    return data;
}

std::size_t UdpLink::send(const bytearray_t& data)
{
    std::size_t data_size = data.size();
    std::size_t bytes_transferred = m_socket.send_to(buffer(data, data_size), m_remote_endpoint);
    return bytes_transferred;
}