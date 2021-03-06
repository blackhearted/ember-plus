/*
    libember -- C++ 03 implementation of the Ember+ Protocol
    Copyright (C) 2012-2014  L-S-B Broadcast Technologies GmbH

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __LIBEMBER_DOM_IMPL_CONTAINER_IPP
#define __LIBEMBER_DOM_IMPL_CONTAINER_IPP

#include <stdexcept>
#include "../../util/Inline.hpp"

namespace libember { namespace dom 
{
    LIBEMBER_INLINE
    Container::Container(ber::Tag tag)
        : Node(tag)
    {}

    LIBEMBER_INLINE
    Container::iterator Container::insert(iterator const& where, Node* child)
    {
        if (child->parent() != 0)
        {
            throw std::runtime_error("Attempt to add a node already owned by a container node.");
        }
        iterator const result = insertImpl(where, child);
        result->setParent(this);
        markDirty();
        return result;
    }

    LIBEMBER_INLINE
    void Container::fixParent(Node* child)
    {
        if (child->parent() != 0)
        {
            throw std::runtime_error("Attempt to reset parent of an already owned child node.");
        }
        child->setParent(this);
    }

    LIBEMBER_INLINE
    void Container::clear()
    {
        erase(begin(), end());
    }

    LIBEMBER_INLINE
    void Container::erase(iterator const& i)
    {
        iterator j = i;
        erase(i, ++j);
    }

    LIBEMBER_INLINE
    void Container::erase(iterator const& first, iterator const& last)
    {
        size_type const oldSize = size();
        try
        {
            eraseImpl(first, last);
        }
        catch (...)
        {
            size_type const newSize = size();
            if (newSize != oldSize)
            {
                markDirty();
            }
            throw;
        }
        markDirty();
    }
}
}

#endif  // __LIBEMBER_DOM_IMPL_CONTAINER_IPP

