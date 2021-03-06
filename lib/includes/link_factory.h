#ifndef LINK_FACTORY_H
#define LINK_FACTORY_H

#include "i_link_factory.h"

#include "link_async.h"

#include <string>
#include <string_view>

namespace loodsman
{
enum class LinkType
{
    udp,
    tcp,
    serial
};

class LinkFactory : public ILinkFactory
{
public:
    LinkFactory() = default;

    LinkAsync* create(const LinkType type, const int localPort,
                      const std::string& localAddress = "0.0.0.0", const int remotePort = 0,
                      const std::string& remoteAddress = "0.0.0.0") noexcept;

    // TODO: Implement serial type    LinkAsync* create(LinkType type ,int baudRate);

    std::string errorMessage() const override;
    int errorCode() const override;

private:
    boost::system::error_code m_errorCode;
};
} // namespace loodsman
#endif //LINK_FACTORY_H
