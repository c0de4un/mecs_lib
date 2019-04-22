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
#ifndef MECS_ENTITIES_MANAGER_HPP
#include "EntitiesManager.hpp"
#endif // !MECS_ENTITIES_MANAGER_HPP

// Include mecs::Entity
#ifndef MECS_ENTITY_HPP
#include "Entity.hpp"
#endif // !MECS_ENTITY_HPP

// ===========================================================
// mecs::EntitiesManager
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	// ===========================================================
	// FIELDS
	// ===========================================================

	/** EntitiesManager instance. **/
	EntitiesManager * EntitiesManager::mInstance( nullptr );

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	 * EntitiesManager constructor.
	 *
	 * @throws - no exceptions.
	**/
	EntitiesManager::EntitiesManager( ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		: mMutex( ), mEntities( )
#else // !MULTI-THREADING
		: mEntities( )
#endif // MULTI-THREADING
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	 * EntitiesManager destructor.
	 *
	 * @throws - no exceptions.
	**/
	EntitiesManager::~EntitiesManager( ) noexcept = default;

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
	EntitiesManager::entity_ptr EntitiesManager::getEntity( const TypeID & pTypeID, const bool pRemove ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_lr( mInstance->mMutex );
#endif // MULTI-THREADING

		// Search Entities vector.
		auto vectorPos_lr = mInstance->mEntities.find( pTypeID );

		// Cancel
		if ( vectorPos_lr == mInstance->mEntities.cend( ) )
			return( entity_ptr( nullptr ) );

		// Get Entities vector.
		entities_vector & entitiesVector_ = vectorPos_lr->second;

		// Cancel
		if ( entitiesVector_.empty( ) )
			return( entity_ptr( nullptr ) );

		// Get Entity
		entity_ptr entity_sp( entitiesVector_.back( ) ); // Copy-construct

		// Remove
		if ( pRemove )
			entitiesVector_.pop_back( );

		// Return Entity
		return( entity_sp ); // Copy-construct

	}

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
	EntitiesManager::entity_ptr EntitiesManager::getEntity( const TypeID & pTypeID, const ObjectID & pID, const bool pRemove ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_lr( mInstance->mMutex );
#endif // MULTI-THREADING

		// Search Entities vector.
		auto vectorPos_lr = mInstance->mEntities.find( pTypeID );

		// Cancel
		if ( vectorPos_lr == mInstance->mEntities.cend( ) )
			return( entity_ptr( nullptr ) );

		// Entities vector.
		entities_vector & entitiesVector_lr = vectorPos_lr->second;

		// Entities vector iterator.
		auto entityPos_l = entitiesVector_lr.begin( );

		// Entities vector end-iterator.
		auto entitiesVecEndIter_l = entitiesVector_lr.cend( );

		// Search Entity
		while ( entityPos_l != entitiesVecEndIter_l )
		{
			// Entity
			entity_ptr & entity_lr = *entityPos_l;

			// Match
			if ( entity_lr->mID == pID )
			{

				// Entity
				entity_ptr entity_sp( entity_lr ); // Copy-construct.

				// Remove Entity
				if ( pRemove )
				{
					std::swap( *entityPos_l, entitiesVector_lr.back( ) );
					entitiesVector_lr.pop_back( );
				}

				// Return
				return( entity_sp ); // Copy-construct

			}

			// Next
			entityPos_l++;

		}

		// Return null
		return( entity_ptr( nullptr ) );

	}

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	 * Initialize EntitiesManager.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void EntitiesManager::Initialize( ) noexcept
	{

		// Cancel
		if ( mInstance != nullptr )
			return;

		// Create EntitiesManager instance.
		mInstance = new EntitiesManager( );

	}

	/**
	 * Terminate EntitiesManager.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void EntitiesManager::Terminate( ) noexcept
	{

		// Cancel
		if ( mInstance == nullptr )
			return;

		// Delete EntitiesManager instance.
		delete mInstance;

		// Reset pointer-value.
		mInstance = nullptr;

	}

	/**
	 * Add Entity.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Entity Type-ID.
	 * @param pEntity - Entity.
	 * @throws - no exceptions.
	**/
	void EntitiesManager::addEntity( const TypeID & pTypeID, EntitiesManager::entity_ptr & pEntity ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_lr( mInstance->mMutex );
#endif // MULTI-THREADING

		// Get Entities vector.
		entities_vector & entitiesVector_lr = mInstance->mEntities[pTypeID];

		// Add Entity
		entitiesVector_lr.push_back( pEntity );

	}

	/**
	 * Removes all Entities of the given Type-ID.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Entity Type-ID.
	 * @throws - no exceptions.
	**/
	void EntitiesManager::clear( const TypeID & pTypeID ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_lr( mInstance->mMutex );
#endif // MULTI-THREADING

		// Search Entities vector.
		auto vectorPos_lr = mInstance->mEntities.find( pTypeID );

		// Cancel
		if ( vectorPos_lr == mInstance->mEntities.cend( ) )
			return;

		// Remove Entities vector.
		mInstance->mEntities.erase( vectorPos_lr );

	}

	// -----------------------------------------------------------

} // mecs

// -----------------------------------------------------------