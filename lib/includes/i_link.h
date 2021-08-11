#ifndef I_LINK_H
#define I_LINK_H

#include <string_view>
#include <string>

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

    virtual std::string errorMessage() const = 0;
    virtual int errorCode() const = 0;

};

} // namespace loodsman
#endif //I_LINK_H