#ifndef UDP_LINK_H
#define UDP_LINK_H

#include "i_link.h"
#include "link_async.h"

#include "utils.h"

#include <boost/asio.hpp>

namespace loodsman
{
class UdpLink final : public LinkAsync
{
public:
    explicit UdpLink(unsigned int localPort, const std::string& localAddress = "0.0.0.0",
                     unsigned int remotePort = 0, const std::string& remoteAddress = "0.0.0.0");

    std::error_code open() override;
    void close() override;

    std::string errorMessage() const override;
    int errorCode() const override;

    std::size_t send(std::string_view data) override;
    std::string receive() override;

    void asyncSend(std::string_view data, SendHandler handler) override;
    void asyncReceive(ReceiveHandler handler) override;

    static void asyncReceiveHandlerWrapper(const boost::system::error_code& errorCode,
                                           std::size_t bytesTransferred, UdpLink* link,
                                           const ReceiveHandler& handler);

    static void asyncSendHandlerWrapper(const boost::system::error_code& errorCode,
                                        std::size_t bytesTransferred, UdpLink* link,
                                        const SendHandler& handler);

private:
    std::error_code bind();
    std::error_code connect();

    [[maybe_unused]] std::string localAddress() const;
    [[maybe_unused]] int localPort() const;

    [[maybe_unused]] std::string remoteAddress() const;
    [[maybe_unused]] int remotePort() const;

    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    boost::asio::ip::udp::endpoint m_localEndpoint;
    char m_buffer[LOODSMAN_MAX_PACKET_LENGTH] = {};
    boost::asio::ip::udp::socket m_socket;
    boost::system::error_code m_errorCode;
};
} // namespace loodsman
#endif // UDP_LINK_H
