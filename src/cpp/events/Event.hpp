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

#ifndef MECS_EVENT_HPP
#define MECS_EVENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs_types.hpp
#ifndef MECS_TYPES_HPP
#include "../cfg/ecs_types.hpp"
#endif // !MECS_TYPES_HPP

// Include mecs::IDMap
#ifndef MECS_ID_MAP_HPP
#include "../utils/IDMap.hpp"
#endif // !MECS_ID_MAP_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	// ===========================================================
	// mecs::Event
	// ===========================================================

// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )

	/**
	 * Event - base data structure used to communicate between Systems & Entities, allowing
	 * to avoid long load time when action, like input, handled during thread lock,
	 * making all other threads (processes) to wait.
	 *
	 * (?) Inspired not as classical ECS Event, but mostly by 'idTech' Events base idea,
	 * with help of C++.
	 *
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	struct Event
	{

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Type-ID. **/
		const TypeID mTypeID;

		/** ID. **/
		const ObjectID mID;

		// ===========================================================
		// FIELDS
		// ===========================================================

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Handled flag. **/
		mecs_abool mHandled;
#else // ONE-THREAD
		/** Handled flag. **/
		bool mHandled;
#endif // MULTI-THREADING

		/** Repeat until handled flag. **/
		bool mRepeat;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * Event constructor.
		 *
		 * @param pTypeID - Event Type-ID.
		 * @param pRepeat - 'true' to keep sending Event until received (handled).
		 * @throws - no exceptions.
		**/
		explicit Event( const TypeID & pTypeID, const bool pRepeat ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * Event destructor.
		 *
		 * @throws - no exceptions.
		**/
		virtual ~Event( ) noexcept;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Events IDs. **/
		static IDMap<const TypeID, ObjectID> mEventsIDs;

		// ===========================================================
		// DELETED
		// ===========================================================

		/* @deleted Event const copy constructor */
		Event( const Event & ) = delete;

		/* @deleted Event const copy assignment operator */
		Event & operator=( const Event & ) = delete;

		/* @deleted Event move constructor */
		Event( Event && ) = delete;

		/* @deleted Event move assignment operator */
		Event & operator=( Event && ) = delete;

		// -----------------------------------------------------------

	}; // mecs::Event

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

	// -----------------------------------------------------------

} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

// mecs::Event
#ifndef MECS_EVENT_DECL
#define MECS_EVENT_DECL
using mecs_Event = mecs::Event;
#endif // !MECS_EVENT_DECL

// -----------------------------------------------------------

#endif // !MECS_EVENT_HPP