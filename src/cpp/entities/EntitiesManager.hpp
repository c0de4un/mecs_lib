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

#ifndef MECS_ENTITIES_MANAGER_HPP
#define MECS_ENTITIES_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include mecs::Entity
#ifndef MECS_ENTITY_HPP
#include "Entity.hpp"
#endif // !MECS_ENTITY_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	/**
	 * EntitiesManager - entities manager. Stores cached Entities.
	 *
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class EntitiesManager final
	{

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIG
		// ===========================================================

		/** Entity pointer. **/
		using entity_ptr = mecs_shared<Entity>;

		/** Entities vector. **/
		using entities_vector = mecs_vector<entity_ptr>;

		/** Entities map. **/
		using entities_map = mecs_map<const TypeID, entities_vector>;

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** EntitiesManager instance. **/
		static EntitiesManager * mInstance;

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex **/
		mecs_mutex mMutex;
#endif // MULTI-THREADING

		/** Entities map. **/
		entities_map mEntities;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * EntitiesManager constructor.
		 *
		 * @throws - no exceptions.
		**/
		explicit EntitiesManager( ) noexcept;

		// ===========================================================
		// DELETED
		// ===========================================================

		/* @deleted EntitiesManager const copy constructor */
		EntitiesManager( const EntitiesManager & ) = delete;

		/* @deleted EntitiesManager const copy assignment operator */
		EntitiesManager & operator=( const EntitiesManager & ) = delete;

		/* @deleted EntitiesManager move constructor */
		EntitiesManager( EntitiesManager && ) = delete;

		/* @deleted EntitiesManager move assignment operator */
		EntitiesManager & operator=( EntitiesManager && ) = delete;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * EntitiesManager destructor.
		 *
		 * @throws - no exceptions.
		**/
		~EntitiesManager( ) noexcept;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		 * Search any Entity of the given Type-ID.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Entity Type-ID.
		 * @param pRemove - 'true' to remove Entity from cache.
		 * @return - Entity, or null.
		 * @throws - no exceptions.
		**/
		static entity_ptr getEntity( const TypeID & pTypeID, const bool pRemove ) noexcept;

		/**
		 * Search any Entity of the given Type-ID & Object-ID.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Entity Type-ID.
		 * @param pID - Entity ID.
		 * @param pRemove - 'true' to remove Entity from cache.
		 * @return - Entity, or null.
		 * @throws - no exceptions.
		**/
		static entity_ptr getEntity( const TypeID & pTypeID, const ObjectID & pID, const bool pRemove ) noexcept;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		 * Initialize EntitiesManager.
		 *
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Initialize( ) noexcept;

		/**
		 * Terminate EntitiesManager.
		 *
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Terminate( ) noexcept;

		/**
		 * Add Entity.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Entity Type-ID.
		 * @param pEntity - Entity.
		 * @throws - no exceptions.
		**/
		static void addEntity( const TypeID & pTypeID, entity_ptr & pEntity ) noexcept;

		/**
		 * Removes all Entities of the given Type-ID.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Entity Type-ID.
		 * @throws - no exceptions.
		**/
		static void clear( const TypeID & pTypeID ) noexcept;

		// -----------------------------------------------------------

	}; // mecs::EntitiesManager

	// -----------------------------------------------------------

} // mecs

// ===========================================================
// CONFIG
// ===========================================================

// -----------------------------------------------------------

#endif // !MECS_ENTITIES_MANAGER_HPP