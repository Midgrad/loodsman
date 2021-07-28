#include "link_factory.h"
// #include "serial_link.h"
// #include "tcp_link.h"
#include "udp_link.h"

loodsman::link_ptr loodsman::factory(loodsman::link_type type, int port, std::string address)
{
    switch (type)
    {
        case link_type::udp:
            if(address == "0.0.0.0")
            {
                return static_cast<link_ptr>(std::make_shared<UdpLink>(port));
            }
            else
            {
                return static_cast<link_ptr>(std::make_shared<UdpLink>(address,port));
            }
            // return nullptr;
            break;
        default:
            debug_print("Unknown link type!");
            return nullptr;
            break;
    }
}