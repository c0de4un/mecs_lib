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

#ifndef MECS_SYSTEMS_MANAGER_HPP
#define MECS_SYSTEMS_MANAGER_HPP

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
	// mecs::SystemsManager
	// ===========================================================

	/**
	 * SystemsManager - handles Systems cache.
	 *
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class SystemsManager final
	{

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIGS
		// ===========================================================

		/** Type-alias for System pointer. **/
		using system_ptr_t = mecs::mecs_shared<System>;

		/** Type-alias for Systems map. **/
		using systems_map_t = mecs_map<const TypeID, system_ptr_t>;

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** SystemsManager instance. **/
		static SystemsManager * mInstance;

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex. **/
		mecs_mutex mMutex;
#endif // MULTI-THREADING

		/** Systems. **/
		systems_map_t mSystems;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * SystemsManager constructor.
		 *
		 * @throws - no exceptions.
		**/
		explicit SystemsManager( ) noexcept;

		// ===========================================================
		// DELETED
		// ===========================================================

		/* @deleted SystemsManager const copy constructor */
		SystemsManager( const SystemsManager & ) = delete;

		/* @deleted SystemsManager const copy assignment operator */
		SystemsManager & operator=( const SystemsManager & ) = delete;

		/* @deleted SystemsManager move constructor */
		SystemsManager( SystemsManager && ) = delete;

		/* @deleted SystemsManager move assignment operator */
		SystemsManager & operator=( SystemsManager && ) = delete;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * SystemsManager destructor.
		 *
		 * @throws - no exceptions.
		**/
		~SystemsManager( ) noexcept;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		 * Search a System with the Type-ID.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - System Type-ID.
		 * @return - System, or null.
		 * @throws - no exceptions.
		**/
		static system_ptr_t getSystem( const TypeID & pTypeID ) noexcept;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		 * Initialize SystemsManager.
		 * 
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Initialize( ) noexcept;

		/**
		 * Terminate SystemsManager.
		 *
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Terminate( ) noexcept;

		/**
		 * Add System to cache.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pSystem - System.
		 * @throws - no exceptions.
		**/
		static void addSystem( system_ptr_t & pSystem ) noexcept;

		/**
		 * Remove System from cache.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - System Type-ID.
		 * @throws - no exceptions.
		**/
		static void removeSystem( const TypeID & pTypeID ) noexcept;

		// -----------------------------------------------------------

	}; // mecs::SystemsManager

	// -----------------------------------------------------------

} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

#ifndef MECS_SYSTEMS_MANAGER_DECL
#define MECS_SYSTEMS_MANAGER_DECL
using mecs_SystemsManager = mecs::SystemsManager;
#endif // !MECS_SYSTEMS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !MECS_SYSTEMS_MANAGER_HPP