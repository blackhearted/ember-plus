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

#ifndef __LIBEMBER_BER_IMPL_VALUE_IPP
#define __LIBEMBER_BER_IMPL_VALUE_IPP

#include "../../util/Inline.hpp"

namespace libember { namespace ber
{
    LIBEMBER_INLINE
    Value::Value()
        : m_payload(0)
    {}
                
    LIBEMBER_INLINE
    Value::Value(Value const& other)
        : m_payload((other.m_payload != 0) ? other.m_payload->addRef() : 0)
    {}

    LIBEMBER_INLINE
    Value::~Value()
    {
        if (m_payload != 0)
        {
            m_payload->releaseRef();
        }
    }

    LIBEMBER_INLINE
    void Value::swap(Value& other)
    {
        using std::swap;
        swap(m_payload, other.m_payload);
    }

    LIBEMBER_INLINE
    Value& Value::operator=(Value other)
    {
        swap(other);
        return *this;
    }

    LIBEMBER_INLINE
    Value::operator bool() const
    {
        return (m_payload != 0);
    }

    LIBEMBER_INLINE
    std::type_info const& Value::typeId() const
    {
        return m_payload->typeId();
    }

    LIBEMBER_INLINE
    Tag Value::universalTag() const
    {
        return m_payload->universalTag();
    }

    LIBEMBER_INLINE
    std::size_t Value::encodedLength() const
    {
        return m_payload->encodedLength();
    }


    LIBEMBER_INLINE
    void Value::encode(util::OctetStream& output) const
    {
        m_payload->encode(output);
    }

    LIBEMBER_INLINE
    Value::Payload::Payload()
        : m_refCount(1)
    {}

    LIBEMBER_INLINE
    Value::Payload::~Payload()
    {}

    LIBEMBER_INLINE
    Value::Payload* Value::Payload::addRef()
    {
        m_refCount += 1;
        return this;
    }

    LIBEMBER_INLINE
    void Value::Payload::releaseRef() 
    {
        m_refCount -= 1;
        if (m_refCount == 0)
        {
            delete this;
        }
    }

}
}

#endif  // __LIBEMBER_BER_IMPL_VALUE_IPP
