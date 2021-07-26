#include "udp_link.h"

using namespace loodsman;

UdpLink::UdpLink(int local_port):
m_local_port(local_port), 
m_local_endpoint(boost::asio::ip::udp::v4(), local_port),
m_socket(m_io)
{

}

bytearray_t UdpLink::receive()
{
    std::size_t bytes_transferred = m_socket.receive_from(boost::asio::buffer(m_buffer), m_remote_endpoint);
    // TODO: Remove both vars
    m_remote_port = m_remote_endpoint.port();
    m_remote_address = m_remote_endpoint.address().to_string();
    
    bytearray_t data;
    data.assign(m_buffer, bytes_transferred);
    return data;
}

int UdpLink::send(const bytearray_t& data)
{
    std::size_t data_size = data.size();
    m_socket.send_to(boost::asio::buffer(data, data_size), m_remote_endpoint);
    return 0;
}
