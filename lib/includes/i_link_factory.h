#ifndef I_LINK_FACTORY_H
#define I_LINK_FACTORY_H

#include "i_link.h"

namespace loodsman
{
class ILinkFactory
{
public:
    virtual ~ILinkFactory() = default;

    // TODO: consider purpose of this header and implementing   virtual ILink* create() = 0;

    virtual std::string errorMessage() const = 0;
    virtual int errorCode() const = 0;
};
} // namespace loodsman
#endif //I_LINK_FACTORY_H
