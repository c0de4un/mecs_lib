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
#ifndef MECS_COMPONENTS_MANAGER_HPP
#include "ComponentsManager.hpp"
#endif // !MECS_COMPONENTS_MANAGER_HPP

// Include mecs::Component
#ifndef MECS_COMPONENT_HPP
#include "Component.hpp"
#endif // !MECS_COMPONENT_HPP

// ===========================================================
// mecs::ComponentsManager
// ===========================================================

namespace mecs
{
	
	// -----------------------------------------------------------
	
	// ===========================================================
	// FIELDS
	// ===========================================================
	
	/** ComponentsManager instance. **/
	ComponentsManager * ComponentsManager::mInstance( nullptr );
	
	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================
	
	/**
	 * ComponentsManager constructor.
	 * 
	 * @throws - no exceptions.
	**/
	ComponentsManager::ComponentsManager( ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		: mComponentsMutex( ), mComponents( )
#else // !MULTI-THREADING
		: mComponents( )
#endif // MULTI-THREADING
	{
	}
	
	// ===========================================================
	// DESTRUCTOR
	// ===========================================================
	
	/**
	 * ComponentsManager destructor.
	 * 
	 * @throws - no exceptions.
	**/ 
	ComponentsManager::~ComponentsManager( ) noexcept = default;

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	 * Initialize ComponentsManager.
	 * 
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void ComponentsManager::Initialize( ) noexcept
	{
		
		// Cancel
		if ( mInstance != nullptr )
			return;
		
		// Create ComponentsManager instance.
		mInstance = new ComponentsManager( );
		
	}

	/**
	 * Terminate ComponentsManager.
	 * 
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void ComponentsManager::Terminate( ) noexcept
	{
		
		// Cancel
		if ( mInstance == nullptr )
			return;
		
		// Delete ComponentsManager instance.
		delete mInstance;
		mInstance = nullptr;
		
	}

	/**
	 * Search for a Component of Type-ID.
	 * 
	 * @thread_safety - thread-lock (synchronization) used.
	 * @param pTypeID - Component Type-ID.
	 * @return - Component, or null.
	 * @throws - no exceptions.
	**/
	ComponentsManager::component_ptr ComponentsManager::getComponent( const TypeID & pTypeID ) noexcept
	{
		
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_l( mInstance->mComponentsMutex );
#endif // MULTI-THREADING
		
		// Search
		auto component_position_l = mInstance->mComponents.find( pTypeID );
		
		// Cancel
		if ( component_position_l == mInstance->mComponents.cend( ) )
			return( component_ptr( nullptr ) );
		
		// Components vector.
		components_vector & componentsVector_lr = component_position_l->second;
		
		// Cancel
		if ( componentsVector_lr.empty( ) )
			return( component_ptr( nullptr ) );
		
		// Pop-Back
		component_ptr component_lp( componentsVector_lr.back( ) ); // Copy-construct
		componentsVector_lr.pop_back( );
		
		// Return Component
		return( component_lp ); // Copy-construct
		
	}

	/**
	 * Add Component to cache.
	 * 
	 * @thread_safety - thread-lock (synchronization) used.
	 * @param pTypeID - Component Type-ID.
	 * @param pComponent - Component.
	 * @throws - no exceptions.
	**/
	void ComponentsManager::addComponent( const TypeID &pTypeID, ComponentsManager::component_ptr & pComponent ) noexcept
	{
		
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_l( mInstance->mComponentsMutex );
#endif // MULTI-THREADING
		
		// Get Components vector.
		components_vector & componentsVector_lr = mInstance->mComponents[pTypeID];
		
		// Add Component
		componentsVector_lr.push_back( pComponent );
		
	}

	/**
	 * Remove all Components with the specific Type-ID.
	 * 
	 * @thread_safety - thread-lock (synchronization) used.
	 * @param pTypeID - Component Type-ID.
	 * @throws - no exceptions.
	**/
	void ComponentsManager::clear( const TypeID & pTypeID ) noexcept
	{
		
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_l( mInstance->mComponentsMutex );
#endif // MULTI-THREADING
		
		// Search
		auto component_position_l = mInstance->mComponents.find( pTypeID );
		
		// Cancel
		if ( component_position_l == mInstance->mComponents.cend( ) )
			return;
		
		// Delete (erase) Components vector.
		mInstance->mComponents.erase( component_position_l );
		
	}

	// -----------------------------------------------------------
	
} // mecs

// -----------------------------------------------------------