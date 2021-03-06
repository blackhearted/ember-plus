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

#ifndef __LIBEMBER_GLOW_GLOWTARGET_HPP
#define __LIBEMBER_GLOW_GLOWTARGET_HPP

#include "GlowSignal.hpp"

namespace libember { namespace glow
{
    /** Forward declarations **/
    class GlowNodeFactory;

    /**
     * Class representing a target description.
     */
    class LIBEMBER_API GlowTarget : public GlowSignal
    {
        friend class GlowNodeFactory;
        public:
            /**
             * Initializes a new instance of GlowTarget
             * @param number The signal number.
             */
            explicit GlowTarget(int number);

            /**
             * Initializes a new instance of GlowTarget
             * @param number The signal number.
             * @param tag The application tag to set
             */
            GlowTarget(int number, ber::Tag const& tag);

        private:
            /**
             * Initializes a new instance of GlowTarget
             * @param tag The application tag to set
             */
            explicit GlowTarget(ber::Tag const& tag);
    };

    /******************************************************
     * Inline Implementation                              *
     ******************************************************/

    inline GlowTarget::GlowTarget(int number, ber::Tag const& tag)
        : GlowSignal(GlowType::Target, tag, number)
    {}

    inline GlowTarget::GlowTarget(ber::Tag const& tag)
        : GlowSignal(GlowType::Target, tag)
    {}

    inline GlowTarget::GlowTarget(int number)
        : GlowSignal(GlowType::Target, number)
    {}
}
}


#endif  // __LIBEMBER_GLOW_GLOWTARGET_HPP
