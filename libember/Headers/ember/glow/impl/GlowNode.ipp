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

#ifndef __LIBEMBER_GLOW_GLOWNODE_IPP
#define __LIBEMBER_GLOW_GLOWNODE_IPP

#include "../../util/Inline.hpp"
#include "../util/ValueConverter.hpp"
#include "../GlowRootElementCollection.hpp"
#include "../GlowNodeBase.hpp"

namespace libember { namespace glow 
{
    LIBEMBER_INLINE
    GlowNode::GlowNode(int number)
        : GlowNodeBase(GlowType::Node, GlowTags::ElementDefault(), GlowTags::Node::Contents(), GlowTags::Node::Children())
        , m_cachedNumber(-1)
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Node::Number(), number));
    }

    LIBEMBER_INLINE
    GlowNode::GlowNode(GlowRootElementCollection* parent, int number)
        : GlowNodeBase(GlowType::Node, GlowTags::ElementDefault(), GlowTags::Node::Contents(), GlowTags::Node::Children())
        , m_cachedNumber(-1)
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Node::Number(), number));
        if (parent)
        {
            GlowRootElementCollection::iterator const where = parent->end();
            parent->insert(where, this);
        }
    }

    LIBEMBER_INLINE
    GlowNode::GlowNode(GlowNodeBase* parent, int number)
        : GlowNodeBase(GlowType::Node, GlowTags::ElementDefault(), GlowTags::Node::Contents(), GlowTags::Node::Children())
        , m_cachedNumber(-1)
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
    GlowNode::GlowNode(int number, ber::Tag const& tag)
        : GlowNodeBase(GlowType::Node, tag, GlowTags::Node::Contents(), GlowTags::Node::Children())
        , m_cachedNumber(-1)
    {
        insert(begin(), new dom::VariantLeaf(GlowTags::Node::Number(), number));
    }

    LIBEMBER_INLINE
    GlowNode::GlowNode(ber::Tag const& tag)
        : GlowNodeBase(GlowType::Node, tag, GlowTags::Node::Contents(), GlowTags::Node::Children())
        , m_cachedNumber(-1)
    {}

    LIBEMBER_INLINE
    int GlowNode::number() const
    {
        if (m_cachedNumber == -1)
        {
            ber::Tag const tag = GlowTags::Node::Number();
            const_iterator const first = begin();
            const_iterator const last = end();
            const_iterator const result = util::find_tag(first, last, tag);
            if (result != last)
            {
                m_cachedNumber = util::ValueConverter::valueOf(&*result, -1);
            }
            else
            {
                m_cachedNumber = -1;
            }
        }

        return m_cachedNumber;
    }

    LIBEMBER_INLINE
    GlowNode::iterator GlowNode::insertImpl(iterator const& where, Node* child)
    {
        m_cachedNumber = -1;
        return GlowContainer::insertImpl(where, child);
    }

    LIBEMBER_INLINE
    void GlowNode::eraseImpl(iterator const& first, iterator const& last)
    {
        m_cachedNumber = -1;
        GlowContainer::eraseImpl(first, last);
    }
}
}

#endif  // __LIBEMBER_GLOW_GLOWNODE_IPP
