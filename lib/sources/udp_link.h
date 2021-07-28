#ifndef UDP_LINK_H
#define UDP_LINK_H

#include "i_link.h"
#include "types.h"

namespace loodsman
{
class UdpLink final : public ILink
{
public:
    UdpLink(int local_port);
    UdpLink(const std::string& remote_address, int remote_port);
    ~UdpLink();

    std::string localAddress() const;
    uint localPort() const;

    std::string remoteAddress() const;
    uint remotePort() const;

    int open() override;
    int close() override;

    std::size_t send(const bytearray_t& data) override;
    bytearray_t receive() override;

private:

    int bind(int port);
    int connect(const std::string& remote_address, int remote_port);

    boost::asio::ip::udp::endpoint m_remote_endpoint;
    byte_t m_buffer[MAX_PACKET_LENGTH];
    boost::asio::ip::udp::socket m_socket;
};
} // namespace 
#endif // UDP_LINK_H
