#include "ILinkFactory.h"
#include "i_link.h"
#include <string_view>

#ifndef LOODSMAN_UDPLINKFACTORY_H
#define LOODSMAN_UDPLINKFACTORY_H

namespace loodsman
{
class UdpLinkFactory : public ILinkFactory
{
public:
    UdpLinkFactory(int local_port);

    UdpLinkFactory(int local_port, std::string local_address);

    UdpLinkFactory(int local_port, std::string local_address, int remote_port,
                   std::string remote_address);

    int create(ILink* link) override;

private:
    const int m_local_port;
    const std::string m_local_address;
    const int m_remote_port;
    const std::string m_remote_address;
};
} // namespace loodsman
#endif //LOODSMAN_UDPLINKFACTORY_H
