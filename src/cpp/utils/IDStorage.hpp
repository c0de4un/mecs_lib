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

#ifndef MECS_IDSTORAGE_HPP
#define MECS_IDSTORAGE_HPP

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
	// mecs::IDStorage
	// ===========================================================
	
	/**
	 * IDStorage - template storage utility-class (pool) for IDs (numeric values).
	 * Useful to replace same code, when generation of the unique IDs required (Entities, Meshes, etc).
	 *
	 * @version 1.0.0
	 * @since 21.03.2019
	 * @authors Denis Z. (code4un@yandex.ru)
	*/
	template <typename IDType>
	class IDStorage final
	{
	
	private:
		
		// -----------------------------------------------------------
		
		// ===========================================================
		// CONFIGS
		// ===========================================================
	
		/** Type-alias for IDs map. **/
		using ids_map = mecs_map<const IDType, bool>;
		
		// ===========================================================
		// FIELDS
		// ===========================================================
		
		/** IDs map. **/
		ids_map mIDs;
		
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex **/
		mecs_mutex mMutex;
#endif // MULTI-THREADING
		
		// ===========================================================
		// DELETED
		// ===========================================================
		
		/* @deleted IDStorage const copy constructor */
		IDStorage( const IDStorage & ) = delete;

		/* @deleted IDStorage const copy assignment operator */
		IDStorage & operator=( const IDStorage & ) = delete;

		/* @deleted IDStorage move constructor */
		IDStorage( IDStorage && ) = delete;

		/* @deleted IDStorage move assignment operator */
		IDStorage & operator=( IDStorage && ) = delete;
		
		// -----------------------------------------------------------
		
	public:
		
		// -----------------------------------------------------------
		
		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================
		
		/* IDStorage constructor */
		explicit IDStorage( ) noexcept
			: mIDs( ), mMutex( )
		{
		}
		
		// ===========================================================
		// DESTRUCTOR
		// ===========================================================
		
		/* IDStorage destructor */
		~IDStorage( ) noexcept = default;
		
		// ===========================================================
		// METHODS
		// ===========================================================
		
		/*
		 * Generates (or search available) ID.
		 *
		 * @thread_safety - thread-lock (synchronization) used.
		 * @return - ID.
		 * @throws - can throw exception:
		 * - bad_alloc ;
		 * - IDs limit reached ;
		 * - mutex-exception ;
		*/
		IDType generateID( ) noexcept
		{
			
			// Lock
			mecs_ulock lock_( mMutex );

			// IDs map end
			auto idsMapEnd( mIDs.cend( ) );

			// IDs map iterator
			auto idsIterator( mIDs.begin( ) );

			// Search available ID
			while ( idsIterator != idsMapEnd )
			{

				// Compare
				if ( !idsIterator->second )
				{// Available ID found
				
					// Reserve ID
					idsIterator->second = true;

					// Return ID
					return( idsIterator->first );

				}

				// Next
				idsIterator++;

			}

			// Create new ID
			const IDType newID( mIDs.size( ) );

			// Register ID
			mIDs.insert( std::pair<const IDType, bool>( newID, true ) );

			// Return ID
			return( newID ); // Copy

		}

		/*
		 * Returns IDs to pool.
		 *
		 * @thread_safety - thread-lock (synchronization) used.
		 * @param pID - ID.
		 * @throws - can throw exception:
		 * - bad_alloc ;
		 * - mutex-exception ;
		*/
		void returnID( const IDType & pID ) noexcept
		{

			// Lock
			mecs_ulock lock_( mMutex );

			// Mark ID as available
			mIDs[pID] = false;

		}
		
		// -----------------------------------------------------------
		
	}; // mecs::IDStorage
	
	// -----------------------------------------------------------
	
} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

template <typename IDType>
using mecs_IDStorage = mecs::IDStorage<IDType>;

// -----------------------------------------------------------

#endif // !MECS_IDSTORAGE_HPP