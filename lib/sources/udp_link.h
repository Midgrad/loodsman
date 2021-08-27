#ifndef UDP_LINK_H
#define UDP_LINK_H

#include "i_link.h"
#include <boost/asio.hpp>

namespace loodsman
{
class UdpLink final : public ILink
{
public:
    explicit UdpLink(int local_port, const std::string& local_address = "0.0.0.0",
                     int remote_port = 0, const std::string& remote_address = "0.0.0.0");

    int open() override;
    int close() override;

    std::string localAddress() const;
    int localPort() const;

    std::string remoteAddress() const;
    int remotePort() const;

    std::string errorMessage() const override;
    int errorCode() const override;

    std::size_t send(std::string_view data) override;
    std::string receive() override;

private:
    int bind(int port);
    int connect(const std::string& remote_address, int remote_port);

    boost::asio::io_context m_io;
    boost::asio::ip::udp::endpoint m_remote_endpoint;
    char m_buffer[MAX_PACKET_LENGTH];
    boost::asio::ip::udp::socket m_socket;
    boost::system::error_code m_errorCode;
};
} // namespace loodsman
#endif // UDP_LINK_H
