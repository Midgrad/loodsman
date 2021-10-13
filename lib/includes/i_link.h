//     Copyright (c) Ilia Kuklev aka Elias Alberts 2021.
//     nnhw667@gmail.com
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef I_LINK_H
#define I_LINK_H

#include <string_view>

namespace loodsman
{
class ILink
{
public:
    virtual ~ILink() = default;

    virtual std::size_t send(std::string_view data) = 0;
    virtual std::string receive() = 0;

    virtual int open() = 0;
    virtual int close() = 0;

    virtual std::string errorMessage() const = 0;
    virtual int errorCode() const = 0;
};

} // namespace loodsman
#endif //I_LINK_H
