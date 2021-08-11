#ifndef I_LINK_H
#define I_LINK_H

//TODO: remove boost specialization
#include <string_view>
#include <boost/asio.hpp>

namespace loodsman
{

class ILink
{
public:
    virtual ~ILink() = default;

    virtual std::size_t send(std::string_view data) = 0;
    virtual std::string_view receive() = 0;

    virtual int open() = 0;
    virtual int close() = 0;

};

} // namespace loodsman
#endif //I_LINK_H