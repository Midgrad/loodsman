#include "udp_link.h"

using namespace loodsman;

UdpLink::UdpLink(int local_port):
m_local_port(local_port), 
m_local_endpoint(boost::asio::ip::udp::v4(), local_port),
m_socket(m_io)
{
    
    // link_bind();
}

bytearray_t UdpLink::receive()
{
    std::size_t bytes_transferred = m_socket.receive_from(boost::asio::buffer(m_buffer), m_remote_endpoint);
    m_remote_port = m_remote_endpoint.port();
    m_remote_address = m_remote_endpoint.address().to_string();
    
    bytearray_t data;
    data.assign(m_buffer, bytes_transferred);
    return data;
}

int UdpLink::send(const bytearray_t& data)
{
    return 0;
}
