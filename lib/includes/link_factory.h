#ifndef LINK_FACTORY_H
#define LINK_FACTORY_H

#include "i_link.h"

namespace loodsman
{

using link_ptr = std::shared_ptr<ILink>;

link_ptr factory(link_type type, int local_port, std::string local_address = "0.0.0.0", int remote_port = 0, std::string remote_address = "0.0.0.0");

} // namespace 
#endif // LINK_FACTORY_H