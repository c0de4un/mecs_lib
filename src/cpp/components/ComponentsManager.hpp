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

#ifndef MECS_COMPONENTS_MANAGER_HPP
#define MECS_COMPONENTS_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs_types.hpp
#ifndef MECS_TYPES_HPP
#include "../cfg/ecs_types.hpp"
#endif // !MECS_TYPES_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// TYPES
// ===========================================================

namespace mecs
{
	
	/**
	 * ComponentsManager - stores cached Components, allowing to pre-allocate
	 * & reuse, to avoid fragmentation of memory & aligned objects collections.
	 * 
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class ComponentsManager final
	{
		
	private:
		
		// -----------------------------------------------------------
		
		// ===========================================================
		// CONFIGS
		// ===========================================================
		
		/** Component pointer. **/
		using component_ptr = mecs_shared<Component>;
		
		/** Components container. **/
		using components_vector = mecs_vector<component_ptr>;
		
		/** Components map. **/
		using components_map = mecs_map<const TypeID, components_vector>;
		
		// ===========================================================
		// CONSTANTS
		// ===========================================================
		
		// ===========================================================
		// FIELDS
		// ===========================================================
		
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex **/
		mecs_mutex mComponentsMutex;
#endif // MULTI-THREADING
		
		/** ComponentsManager instance. **/
		static ComponentsManager * mInstance;
		
		/** Components map. **/
		components_map mComponents;
		
		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================
		
		/**
		 * ComponentsManager constructor.
		 * 
		 * @throws - no exceptions.
		**/
		explicit ComponentsManager( ) noexcept;
		
		// ===========================================================
		// DELETED
		// ===========================================================
		
		explicit ComponentsManager( const ComponentsManager & ) noexcept = delete;
		ComponentsManager & operator=( const ComponentsManager & ) noexcept = delete;
		explicit ComponentsManager( ComponentsManager && ) noexcept = delete;
		ComponentsManager & operator=( ComponentsManager && ) noexcept = delete;
		
		// -----------------------------------------------------------
		
	public:
	
		// -----------------------------------------------------------
		
		// ===========================================================
		// DESTRUCTOR
		// ===========================================================
		
		/**
		 * ComponentsManager destructor.
		 * 
		 * @throws - no exceptions.
		**/ 
		~ComponentsManager( ) noexcept;
		
		// ===========================================================
		// METHODS
		// ===========================================================
		
		/**
		 * Initialize ComponentsManager.
		 * 
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Initialize( ) noexcept;
		
		/**
		 * Terminate ComponentsManager.
		 * 
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/ 
		static void Terminate( ) noexcept;
		
		/**
		 * Search for a Component of Type-ID.
		 * 
		 * @thread_safety - thread-lock (synchronization) used.
		 * @param pTypeID - Component Type-ID.
		 * @return - Component, or null.
		 * @throws - no exceptions.
		**/ 
		static component_ptr getComponent( const TypeID & pTypeID ) noexcept;
		
		/**
		 * Add Component to cache.
		 * 
		 * @thread_safety - thread-lock (synchronization) used.
		 * @param pTypeID - Component Type-ID.
		 * @param pComponent - Component.
		 * @throws - no exceptions.
		**/
		static void addComponent( const TypeID & pTypeID, component_ptr & pComponent ) noexcept;
		
		/**
		 * Remove all Components with the specific Type-ID.
		 * 
		 * @thread_safety - thread-lock (synchronization) used.
		 * @param pTypeID - Component Type-ID.
		 * @throws - no exceptions.
		**/ 
		static void clear( const TypeID & pTypeID ) noexcept;
		
		// -----------------------------------------------------------
		
	}; // mecs::ComponentsManager
	
} // mecs

// ===========================================================
// CONFIG
// ===========================================================

#ifndef MECS_COMPONENTS_MANAGER_DECL
#define MECS_COMPONENTS_MANAGER_DECL
using mecs_ComponentsManager = mecs::ComponentsManager;
#endif // !MECS_COMPONENTS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !MECS_COMPONENTS_MANAGER_HPP