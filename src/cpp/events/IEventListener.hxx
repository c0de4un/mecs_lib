/**
* Copyright © 2019 Denis Zyamaev (code4un@yandex.ru) All rights reserved.
* Authors: Denis Zyamaev (code4un@yandex.ru)
* All rights reserved.
* Language: C++
* License: see LICENSE.txt
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must display the names 'Denis Zyamaev' and
* in the credits of the application, if such credits exist.
* The authors of this work must be notified via email (code4un@yandex.ru) in
* this case of redistribution.
* 3. Neither the name of copyright holders nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
* IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef MECS_I_EVENT_LISTENER_HPP
#define MECS_I_EVENT_LISTENER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs_types.hpp
#ifndef MECS_TYPES_HPP
#include "../cfg/ecs_types.hpp"
#endif // !MECS_TYPES_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	// ===========================================================
	// mecs::IEventListener
	// ===========================================================

	/**
	 * IEventListener - interface to catch (handle) Events.
	 *
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class IEventListener
	{

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * IEventListener destructor.
		 * 
		 * @throws - no exceptions.
		**/
		virtual ~IEventListener( ) noexcept = default;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		 * Called when Event raised.
		 * 
		 * @thread_safety - not required, async-queue used.
		 * @param pEvent - Event.
		 * @return - 'true' if handled.
		 * @throws - no exceptions.
		**/
		virtual bool onEvent( mecs_shared<Event> & pEvent ) noexcept = 0;

		// -----------------------------------------------------------

	}; // mecs::IEventListener

	// -----------------------------------------------------------

} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

#ifndef MECS_I_EVENT_LISTENER_DECL
#define MECS_I_EVENT_LISTENER_DECL
using mecs_IEventListener = mecs::IEventListener;
#endif // !MECS_I_EVENT_LISTENER_DECL

// -----------------------------------------------------------

#endif // !MECS_I_EVENT_LISTENER_HPP