#include "link_factory.h"
// #include "serial_link.h"
// #include "tcp_link.h"
#include "udp_link.h"

using namespace loodsman;

link_ptr factory(link_type type, int local_port, std::string local_address = "0.0.0.0", int remote_port = NULL, std::string remote_address = "")
{
    link_ptr l_link = nullptr;
    switch (type)
    {
        case link_type::udp:

            try 
            {
                l_link = static_cast<link_ptr>(std::make_shared<UdpLink>(local_port));
            }
            catch (...)
            {
                debug_print("Generic error");
            }
                 
            return l_link;
            break;
        default:
            debug_print("Unknown link type!");
            return l_link;
            break;
    }
}