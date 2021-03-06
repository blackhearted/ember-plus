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

#ifndef __LIBEMBER_DOM_IMPL_VARIANTLEAF_IPP
#define __LIBEMBER_DOM_IMPL_VARIANTLEAF_IPP

#include "../../util/Inline.hpp"
#include "../../ber/Encoding.hpp"

namespace libember { namespace dom
{
    LIBEMBER_INLINE
    VariantLeaf::VariantLeaf(ber::Tag tag)
        : Node(tag), m_value(), m_cachedLength(0)
    {}

    LIBEMBER_INLINE
    VariantLeaf::VariantLeaf(ber::Tag tag, ber::Value value)
        : Node(tag), m_value(value), m_cachedLength(0)
    {}

    LIBEMBER_INLINE
    VariantLeaf::VariantLeaf(VariantLeaf const& other)
        : Node(static_cast<Node const&>(other)), m_value(other.m_value),
            m_cachedLength(0)
    {}

    LIBEMBER_INLINE
    VariantLeaf* VariantLeaf::clone() const
    {
        return new VariantLeaf(*this);
    }

    LIBEMBER_INLINE
    ber::Value VariantLeaf::value() const
    {
        return m_value;
    }

    LIBEMBER_INLINE
    void VariantLeaf::setValue(ber::Value value)
    {
        m_value.swap(value);
        markDirty();
    }

    LIBEMBER_INLINE
    ber::Tag VariantLeaf::typeTagImpl() const
    {
        return m_value.universalTag();
    }

    LIBEMBER_INLINE
    void VariantLeaf::updateImpl() const
    {
        std::size_t const innerTagLength = ber::encodedLength(typeTag());
        std::size_t const payloadLength  = m_value.encodedLength();
        std::size_t const innerLength    = innerTagLength + ber::encodedLength(ber::make_length(payloadLength)) + payloadLength;

        std::size_t const outerTagLength = ber::encodedLength(applicationTag().toContainer());
        std::size_t const outerLength    = outerTagLength + ber::encodedLength(ber::make_length(innerLength)) + innerLength;

        m_cachedLength = outerLength;
    }

    LIBEMBER_INLINE
    void VariantLeaf::encodeImpl(util::OctetStream& output) const
    {
        ber::Tag const innerTag = typeTag();
        std::size_t const innerTagLength = ber::encodedLength(innerTag);
        std::size_t const payloadLength  = m_value.encodedLength();
        std::size_t const innerLength    = innerTagLength + ber::encodedLength(ber::make_length(payloadLength)) + payloadLength;
        
        // Encode the outer frame (as a container)
        ber::encode(output, applicationTag().toContainer());
        ber::encode(output, ber::make_length(innerLength));
        
        // Encode the inner frame
        ber::encode(output, innerTag);
        ber::encode(output, ber::make_length(payloadLength));

        // Encode the value
        m_value.encode(output);
    }

    LIBEMBER_INLINE
    std::size_t VariantLeaf::encodedLengthImpl() const
    {
        return m_cachedLength;
    }
}
}

#endif  // __LIBEMBER_DOM_IMPL_VARIANTLEAF_IPP

