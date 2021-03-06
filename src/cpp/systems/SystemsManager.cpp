/**
* Copyright � 2019 Denis Zyamaev (code4un@yandex.ru) All rights reserved.
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
#ifndef MECS_SYSTEMS_MANAGER_HPP
#include "SystemsManager.hpp"
#endif // !MECS_SYSTEMS_MANAGER_HPP

// Include mecs::System
#ifndef MECS_SYSTEM_HPP
#include "System.hpp"
#endif // !MECS_SYSTEM_HPP

// ===========================================================
// mecs::SystemsManager
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	// ===========================================================
	// FIELDS
	// ===========================================================

	/** SystemsManager instance. **/
	SystemsManager * SystemsManager::mInstance( nullptr );

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	 * SystemsManager constructor.
	 *
	 * @throws - no exceptions.
	**/
	SystemsManager::SystemsManager( ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		: mMutex( ), mSystems( )
#else // ONE-THREAD
		: mSystems( )
#endif // MULTI-THREADING
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	 * SystemsManager destructor.
	 *
	 * @throws - no exceptions.
	**/
	SystemsManager::~SystemsManager( ) noexcept = default;

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
	SystemsManager::system_ptr_t SystemsManager::getSystem( const TypeID & pTypeID ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mMutex );
#endif // MULTI-THREADING

		// Search System
		auto systemPos_ = mInstance->mSystems.find( pTypeID );

		// Cancel
		if ( systemPos_ == mInstance->mSystems.cend( ) )
			return( system_ptr_t( nullptr ) );

		// Return System
		return( systemPos_->second ); // Copy-construct

	}

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	 * Initialize SystemsManager.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void SystemsManager::Initialize( ) noexcept
	{

		// Cancel
		if ( mInstance != nullptr )
			return;

		// Create SystemsManager instance.
		mInstance = new SystemsManager( );

	}

	/**
	 * Terminate SystemsManager.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void SystemsManager::Terminate( ) noexcept
	{

		// Cancel
		if ( mInstance == nullptr )
			return;

		// Delete SystemsManager instance.
		delete mInstance;
		mInstance = nullptr;

	}

	/**
	 * Add System to cache.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pSystem - System.
	 * @throws - no exceptions.
	**/
	void SystemsManager::addSystem( system_ptr_t & pSystem ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mMutex );
#endif // MULTI-THREADING

		// Add System
		mInstance->mSystems.insert( std::pair<const TypeID, system_ptr_t>( pSystem->mTypeID, pSystem ) );

	}

	/**
	 * Remove System from cache.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - System Type-ID.
	 * @throws - no exceptions.
	**/
	void SystemsManager::removeSystem( const TypeID & pTypeID ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mMutex );
#endif // MULTI-THREADING

		// Search System
		auto systemPos_ = mInstance->mSystems.find( pTypeID );

		// Cancel
		if ( systemPos_ == mInstance->mSystems.cend( ) )
			return;

		// Remove System
		mInstance->mSystems.erase( systemPos_ );

	}

	// -----------------------------------------------------------

} // mecs

// -----------------------------------------------------------