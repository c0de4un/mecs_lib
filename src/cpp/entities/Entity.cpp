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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef MECS_ENTITY_HPP
#include "Entity.hpp"
#endif // !MECS_ENTITY_HPP

// ===========================================================
// mecs::Entity
// ===========================================================

namespace mecs
{
	
	// -----------------------------------------------------------
	
	// ===========================================================
	// FIELDS
	// ===========================================================
	
	/** Entities IDs Storage. **/
	IDMap<const TypeID, ObjectID> Entity::mIDStorage;
	
	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================
	
	/**
	 * Entity constructor.
	 * 
	 * @param pType - Entity Type-ID.
	 * @throws - no exceptions.
	**/
	Entity::Entity( const TypeID & pType ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		: mMutex( ), mComponents( ),
#else // !MULTI-THREADING
		: mComponents( ),
#endif // MULTI-THREADING
		mTypeID( pType ),
	 	mID( mIDStorage.generateID( pType ) )
	{
	}
	
	// ===========================================================
	// DESTRUCTOR
	// ===========================================================
	
	/**
	 * Entity destructor.
	 * 
	 * @throws - no exceptions.
	**/
	Entity::~Entity( ) noexcept
	{
	
		// Return ID
		mIDStorage.returnID( mTypeID, mID );
	
	}
	
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
	Entity::component_ptr Entity::getComponent( const TypeID & pTypeID ) noexcept
	{
	
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_l( mMutex );
#endif // MULTI-THREADING
	
		// Search
		auto componentPosition_lr = mComponents.find( pTypeID );
	
		// Cancel
		if ( componentPosition_lr == mComponents.cend( ) )
			return( component_ptr( nullptr ) );
	
		// Return Component
		return( componentPosition_lr->second ); // Copy-construct.
	
	}
	
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
	void Entity::attachComponent( const TypeID & pTypeID, Entity::component_ptr & pComponent ) noexcept
	{
	
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_l( mMutex );
#endif // MULTI-THREADING
	
		// Add Component
		mComponents[pTypeID] = pComponent;
	
	}
	
	/**
	 * Detach Component.
	 * 
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Component Type-ID.
	 * @throws - no exceptions.
	**/
	void Entity::detachComponent( const TypeID & pTypeID ) noexcept
	{
	
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_l( mMutex );
#endif // MULTI-THREADING
	
		// Remove Component
		mComponents.erase( pTypeID );
	
	}
	
	// -----------------------------------------------------------
	
} // mecs

// -----------------------------------------------------------