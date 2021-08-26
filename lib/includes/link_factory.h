#ifndef LINK_FACTORY_H
#define LINK_FACTORY_H

#include <memory>

#include "i_link.h"

namespace loodsman
{
enum class link_type
{
    unknown,
    udp,
    tcp,
    serial
};

using LinkPtr = std::shared_ptr<ILink>;

// TODO: use boost::system::error_code or similar
int factory(LinkPtr& linkOut, link_type type, int local_port, std::string local_address = "0.0.0.0",
            int remote_port = 0, std::string remote_address = "0.0.0.0");

} // namespace loodsman
#endif // LINK_FACTORY_H
