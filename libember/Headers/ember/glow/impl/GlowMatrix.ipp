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

#ifndef __LIBEMBER_GLOW_GLOWMATRIX_IPP
#define __LIBEMBER_GLOW_GLOWMATRIX_IPP

#include "../../util/Inline.hpp"
#include "../util/ValueConverter.hpp"
#include "../GlowRootElementCollection.hpp"
#include "../GlowNodeBase.hpp"

namespace libember { namespace glow 
{
    LIBEMBER_INLINE
    GlowMatrix::GlowMatrix(int number)
        : GlowMatrixBase(
            GlowType::Matrix,
            GlowTags::ElementDefault(),
            GlowTags::Matrix::Contents(),
            GlowTags::Matrix::Children(),
            GlowTags::Matrix::Targets(),
            GlowTags::Matrix::Sources(),
            GlowTags::Matrix::Connections())
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Matrix::Number(), number));
    }

    LIBEMBER_INLINE
    GlowMatrix::GlowMatrix(GlowRootElementCollection* parent, int number)
        : GlowMatrixBase(
            GlowType::Matrix,
            GlowTags::ElementDefault(),
            GlowTags::Matrix::Contents(),
            GlowTags::Matrix::Children(),
            GlowTags::Matrix::Targets(),
            GlowTags::Matrix::Sources(),
            GlowTags::Matrix::Connections())
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Matrix::Number(), number));
        if (parent)
        {
            GlowRootElementCollection::iterator const where = parent->end();
            parent->insert(where, this);
        }
    }

    LIBEMBER_INLINE
    GlowMatrix::GlowMatrix(GlowNodeBase* parent, int number)
        : GlowMatrixBase(
            GlowType::Matrix,
            GlowTags::ElementDefault(),
            GlowTags::Matrix::Contents(),
            GlowTags::Matrix::Children(),
            GlowTags::Matrix::Targets(),
            GlowTags::Matrix::Sources(),
            GlowTags::Matrix::Connections())
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Node::Number(), number));
        if (parent)
        {
            GlowElementCollection* children = parent->children();
            GlowElementCollection::iterator const where = children->end();
            children->insert(where, this);
        }
    }

    LIBEMBER_INLINE
    GlowMatrix::GlowMatrix(int number, ber::Tag const& tag)
        : GlowMatrixBase(
            GlowType::Matrix,
            tag,
            GlowTags::Matrix::Contents(),
            GlowTags::Matrix::Children(),
            GlowTags::Matrix::Targets(),
            GlowTags::Matrix::Sources(),
            GlowTags::Matrix::Connections())
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Node::Number(), number));
    }

    LIBEMBER_INLINE
    GlowMatrix::GlowMatrix(ber::Tag const& tag)
        : GlowMatrixBase(
            GlowType::Matrix,
            tag,
            GlowTags::Matrix::Contents(),
            GlowTags::Matrix::Children(),
            GlowTags::Matrix::Targets(),
            GlowTags::Matrix::Sources(),
            GlowTags::Matrix::Connections())
    {}

    LIBEMBER_INLINE
    int GlowMatrix::number() const
    {
        ber::Tag const tag = GlowTags::Node::Number();
        const_iterator const first = begin();
        const_iterator const last = end();
        const_iterator const result = util::find_tag(first, last, tag);
        if (result != last)
        {
            return util::ValueConverter::valueOf(&*result, -1);
        }
        else
        {
            return -1;
        }
    }
}
}

#endif  // __LIBEMBER_GLOW_GLOWMATRIX_IPP
