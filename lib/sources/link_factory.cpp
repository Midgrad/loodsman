#include "link_factory.h"
// #include "serial_link.h"
// #include "tcp_link.h"
#include "udp_link.h"
#include "utils.h"

using namespace loodsman;

int loodsman::factory(LinkPtr& linkOut, link_type type, int local_port, std::string local_address,
                      int remote_port, std::string remote_address)
{
    switch (type)
    {
    case link_type::udp:

        try
        {
            linkOut = static_cast<LinkPtr>(
                std::make_shared<UdpLink>(local_port, local_address, remote_port, remote_address));
        }
        catch (const boost::system::system_error& error)
        {
            debug_print("boost system error");
            return -1;
        }
        catch (...)
        {
            debug_print("Generic error");
            return -1;
        }

        return 0;
        break;
    default:
        debug_print("Unknown link type!");
        return -1;
        break;
    }
}
