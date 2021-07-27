#include "udp_link.h"

using namespace loodsman;

UdpLink::UdpLink(int local_port):
m_local_endpoint(ip::udp::v4(), local_port),
m_socket(m_io,m_local_endpoint)
{
    // this->open();
}

UdpLink::UdpLink(const std::string& remote_address, int remote_port):
m_remote_endpoint(ip::make_address(remote_address), remote_port),
m_socket(m_io)
{
    this->open();
}

UdpLink::~UdpLink()
{
    this->close();
}

void UdpLink::open()
{
    m_socket.open(ip::udp::v4());
}

void UdpLink::close()
{
    m_socket.close();
}

std::string UdpLink::address() const
{
    return m_socket.local_endpoint().address().to_string();
}

uint UdpLink::port() const
{
    return m_socket.local_endpoint().port();
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

using link_ptr = std::shared_ptr<loodsman::ILink>;