#ifndef LINK_FACTORY_H
#define LINK_FACTORY_H

#include "i_link.h"

namespace loodsman
{
    
link_ptr factory(link_type type, int port, std::string address = "0.0.0.0");

} // namespace 
#endif // LINK_FACTORY_H