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

    std::string address() const;
    uint32_t port() const;

    void open() override;
    void close() override;

    int send(const bytearray_t& data) override;
    bytearray_t receive() override;

private:
    boost::asio::ip::udp::endpoint m_local_endpoint;
    boost::asio::ip::udp::endpoint m_remote_endpoint;
    byte_t m_buffer[MAX_PACKET_LENGTH];
    boost::asio::ip::udp::socket m_socket;
};
} // namespace 
#endif // UDP_LINK_H
