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

#ifndef MECS_COMPONENT_HPP
#define MECS_COMPONENT_HPP

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
	
// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )
	
	// ===========================================================
	// mecs::Component
	// ===========================================================

	/**
	 * Component - base Component structure. Components should contain only
	 * data, no logic.
	 * 
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	struct Component
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
		
		/** Remove flag. Used to automatically remove Component from System. **/
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		mecs_abool mRemove;
#else // ONE-THREAD
		bool mRemove;
#endif // MULTI-THREADING
		
		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * Component constructor.
		 *
		 * @param pType - Component Type-ID.
		 * @throws - no exceptions.
		**/
		explicit Component( const TypeID & pType ) noexcept;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * Component destructor.
		 *
		 * @throws - no exceptions.
		**/
		virtual ~Component( ) noexcept;

		// -----------------------------------------------------------

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Components IDs Cache. **/
		static IDMap<const TypeID, ObjectID> mComponentsIDs;

		// ===========================================================
		// DELETED
		// ===========================================================

		/* @deleted Component const copy constructor */
		Component( const Component & ) = delete;

		/* @deleted Component const copy assignment operator */
		Component & operator=( const Component & ) = delete;

		/* @deleted Component move constructor */
		Component( Component && ) = delete;

		/* @deleted Component move assignment operator */
		Component & operator=( Component && ) = delete;

		// -----------------------------------------------------------
		
	}; // mecs::Component

// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )

	// -----------------------------------------------------------
	
} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

#ifndef MECS_COMPONENT_DECL
#define MECS_COMPONENT_DECL
using mecs_Component = mecs::Component;
#endif // !MECS_COMPONENT_DECL

// -----------------------------------------------------------

#endif // !MECS_COMPONENT_HPP