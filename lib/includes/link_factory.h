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
    LinkFactory();

    LinkAsync* create(LinkType type, int localPort, const std::string& localAddress = "0.0.0.0",
                      int remotePort = 0, const std::string& remoteAddress = "0.0.0.0");

    //    LinkAsync* create(LinkType type ,int baudRate);

    int errorCode() const override;

private:
    int m_errorCode;

public:
};
} // namespace loodsman
#endif //LINK_FACTORY_H
