#ifndef LOODSMAN_ILINKFACTORY_H
#define LOODSMAN_ILINKFACTORY_H

#include "i_link.h"

namespace loodsman
{
class ILinkFactory
{
public:
    virtual ~ILinkFactory() = default;

    virtual int create(ILink* link) = 0;
};
} // namespace loodsman
#endif //LOODSMAN_ILINKFACTORY_H
