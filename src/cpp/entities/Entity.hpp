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

#ifndef MECS_ENTITY_HPP
#define MECS_ENTITY_HPP

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
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// TYPES
// ===========================================================

namespace mecs
{
	
	// -----------------------------------------------------------
	
	// ===========================================================
	// mecs::Entity
	// ===========================================================
	
// Enable structure-data (fields, variables) alignment (by compilator) to 1 byte
#pragma pack( push, 1 )
	
	/**
	 * Entity - handles logic of managing Components & interacting with Systems via Events.
	 * 
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class Entity
	{
		
	private:

		// -----------------------------------------------------------

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** Entities IDs Storage. **/
		static IDMap<const TypeID, ObjectID> mIDStorage;

		// -----------------------------------------------------------

	protected:
	
		// -----------------------------------------------------------
		
		// ===========================================================
		// CONFIGS
		// ===========================================================
		
		/** Component pointer. **/
		using component_ptr = mecs_shared<Component>;
		
		/** Components map. **/
		using components_map = mecs_map<const TypeID, component_ptr>;
		
		// ===========================================================
		// FIELDS
		// ===========================================================
		
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex **/
		mecs_mutex mMutex;
#endif // MULTI-THREADING
		
		/** Components. **/
		components_map mComponents;
		
		// ===========================================================
		// DELETED
		// ===========================================================
		
		explicit Entity( const Entity & ) noexcept = delete;
		Entity & operator=( const Entity & ) noexcept = delete;
		explicit Entity( Entity && ) noexcept = delete;
		Entity & operator=( Entity && ) noexcept = delete;
		
		// -----------------------------------------------------------
		
	public:
		
		// -----------------------------------------------------------
		
		// ===========================================================
		// CONSTANTS
		// ===========================================================
		
		/** Type-ID. **/
		const TypeID mTypeID;

		/** Entity-ID. **/
		const ObjectID mID;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================
		
		/**
		 * Entity constructor.
		 * 
		 * @param pType - Entity Type-ID.
		 * @throws - no exceptions.
		**/
		explicit Entity( const TypeID & pType ) noexcept;
		
		// ===========================================================
		// DESTRUCTOR
		// ===========================================================
		
		/**
		 * Entity destructor.
		 * 
		 * @throws - no exceptions.
		**/
		virtual ~Entity( ) noexcept;
		
		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================
		
		/**
		 * Search a Component with specific Type-ID.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Component Type-ID.
		 * @return - Component, or null.
		 * @throws - no exceptions.
		**/
		component_ptr getComponent( const TypeID & pTypeID ) noexcept;
		
		// ===========================================================
		// METHODS
		// ===========================================================
		
		/**
		 * Attach Component.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Component Type-ID.
		 * @param pComponent - Component to attach.
		 * @throws - no exceptions.
		**/
		void attachComponent( const TypeID & pTypeID, component_ptr & pComponent ) noexcept;
		
		/**
		 * Detach Component.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Component Type-ID.
		 * @throws - no exceptions.
		**/
		void detachComponent( const TypeID & pTypeID ) noexcept;
		
		// -----------------------------------------------------------
		
	}; // mecs::Entity
	
// Restore structure-data alignment to default (8-byte on MSVC)
#pragma pack( pop )
	
	// -----------------------------------------------------------
	
} // mecs

// ===========================================================
// CONFIG
// ===========================================================

#ifndef MECS_ENTITY_DECL
#define MECS_ENTITY_DECL
using mecs_Entity = mecs::Entity;
#endif // !MECS_ENTITY_DECL

// -----------------------------------------------------------

#endif // !MECS_ENTITY_HPP