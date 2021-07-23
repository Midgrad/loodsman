#ifndef UDP_LINK_H
#define UDP_LINK_H

#include "abstract_link.h"
#include "types.h"

namespace loodsman
{
class UdpLink final : public AbstractLink
{
public:
    UdpLink(int local_port);
    UdpLink();

    std::string address() const;
    uint32_t port() const;

    int send(const bytearray_t& data) override;
    bytearray_t receive() override;

private:
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_local_endpoint;
    const uint m_local_port;
    const std::string m_local_address{"127.0.0.1"};
    boost::asio::ip::udp::endpoint m_remote_endpoint;
    int m_remote_port;
    std::string m_remote_address;
    byte_t m_buffer[MAX_PACKET_LENGTH];

};
} // namespace 
#endif // UDP_LINK_H
