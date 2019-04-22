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

#ifndef MECS_ID_MAP_HPP
#define MECS_ID_MAP_HPP

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

	/**
	 * IDMap - utility-class to store IDs (values), sorted by type.
	 * 
	 * @version 1.0.0
	 * @since 21.03.2019
	 * @authors Denis Z. (code4un@yandex.ru)
	**/
	template <typename T, typename ID_t>
	class IDMap final
	{

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIGS
		// ===========================================================

		/** Type-alias for IDs map. **/
		using ids_map_t = mecs_map<ID_t, bool>;

		/** Type-alias for IDs maps. **/
		using ids_maps_t = mecs_map<T, ids_map_t>;

		// ===========================================================
		// FIELDS
		// ===========================================================

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex **/
		mecs_mutex mMutex;
#endif // MULTI-THREADING

		/** IDs. **/
		ids_maps_t mIDs;

		// ===========================================================
		// DELETED
		// ===========================================================

		/* @deleted IDMap const copy constructor */
		IDMap( const IDMap & ) = delete;

		/* @deleted IDMap const copy assignment operator */
		IDMap & operator=( const IDMap & ) = delete;

		/* @deleted IDMap move constructor */
		IDMap( IDMap && ) = delete;

		/* @deleted IDMap move assignment operator */
		IDMap & operator=( IDMap && ) = delete;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * IDMap constructor.
		 *
		 * @throws - no exceptions.
		**/
		explicit IDMap( ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
			: mMutex( ), mIDs( )
#else // ONE-THREAD
			: mIDs( )
#endif // MULTI-THREADING
		{
		}

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * IDMap destructor.
		 *
		 * @throws - no exceptions.
		**/
		~IDMap( ) noexcept = default;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		 * Search available ID of the given Type-ID.
		 * 
		 * (!) ID must be returned, when not required.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Type-ID.
		 * @return - ID.
		 * @throws - no exceptions.
		**/
		const ID_t generateID( const T & pTypeID ) noexcept
		{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
			// Lock
			mecs_ulock lock_( mMutex );
#endif // MULTI-THREADING

			// Get IDs map.
			ids_map_t & idsMap_lr = mIDs[pTypeID];

			// IDs map iterator.
			auto idsIter_ = idsMap_lr.begin( );

			// IDs map end-iterator.
			auto idsMapEndIter_ = idsMap_lr.cend( );

			// Search ID
			while ( idsIter_ != idsMapEndIter_ )
			{

				//Check ID status.
				if ( idsIter_->second == false )
				{

					// Copy ID-value
					const ID_t id_( idsIter_->first ); // Copy

					// Reserve ID
					idsIter_->second = true;

					// Return ID
					return( id_ ); // Copy

				}

				// Next ID
				idsIter_++;

			}

			// Create new ID
			const ID_t id_( (ID_t) idsMap_lr.size( ) );

			// Add ID
			idsMap_lr[id_] = true;

			// Return ID
			return( id_ ); // Copy

		}

		/**
		 * Returns ID for reuse.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Type-ID.
		 * @@param pID - ID.
		 * @throws - no exceptions.
		**/
		void returnID( const T & pTypeID, const ID_t & pID ) noexcept
		{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
			// Lock
			mecs_ulock lock_( mMutex );
#endif // MULTI-THREADING

			// Get IDs map.
			ids_map_t & idsMap_lr = mIDs[pTypeID];

			// Reset ID
			idsMap_lr[pID] = false;

		}

		// -----------------------------------------------------------

	}; // mecs::IDMap

} // mecs

// ===========================================================
// CONFIG
// ===========================================================

// -----------------------------------------------------------

#endif // !MECS_ID_MAP_HPP