#ifndef I_LINK_ASYNC_H
#define I_LINK_ASYNC_H

#include "i_link.h"

#include <functional>
#include <string_view>

namespace loodsman
{
using ReceiveHandler = std::function<void(std::string)>;
using SendHandler = std::function<void(std::size_t)>;

class ILinkAsync : public ILink
{
public:
    virtual void asyncSend(std::string_view data, SendHandler handler) = 0;
    virtual void asyncReceive(ReceiveHandler) = 0;
};

} // namespace loodsman
#endif //I_LINK_ASYNC_H
