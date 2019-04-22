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

#ifndef MECS_SYSTEM_HPP
#define MECS_SYSTEM_HPP

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
	// mecs::System
	// ===========================================================

	/**
	 * System - system handles logic, using Components as data-providers, & Events
	 * for communication with Entities & other Systems (Physics & Render).
	 *
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class System
	{

	protected:

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIGS
		// ===========================================================

		/** Type-alias for Component. **/
		using compoent_ptr = mecs_shared<Component>;

		// ===========================================================
		// FIELDS
		// ===========================================================

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Mutex **/
		mecs_mutex mMutex;

		/** Enabled flag. **/
		mecs_abool mEnabled;
#else // ONE-THREAD
		/** Enabled flag. **/
		bool mEnabled;
#endif // MULTI-THREADING

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * System constructor.
		 *
		 * @param pTypeID - System Type-ID.
		 * @throws - no exceptions.
		**/
		explicit System( const TypeID & pTypeID ) noexcept;

		// ===========================================================
		// DELETED
		// ===========================================================

		explicit System( const System & ) noexcept = delete;
		System & operator=( const System & ) noexcept = delete;
		explicit System( System && ) noexcept = delete;
		System & operator=( System && ) noexcept = delete;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// CONSTANTS
		// ===========================================================

		/** Type-ID. **/
		const TypeID mTypeID;

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * System destructor.
		 * 
		 * @throws - no exceptions.
		**/
		virtual ~System( ) noexcept;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		 * Returns 'true' if this System is Enabled.
		 *
		 * @thread_safety - atomic-flag used.
		 * @throws - no exceptions.
		**/
		virtual bool isEnabled( ) const noexcept;

		/**
		 * Enabled || Disable System.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pEnabled - 'true' to Enable, 'false' to Disable.
		 * @throws - no exceptions.
		**/
		virtual void setEnabled( const bool pEnabled ) noexcept = 0;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		 * Add Component.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Component Type-ID.
		 * @param pComponent - Component.
		 * @throws - no exceptions.
		**/
		virtual void addComponent( const TypeID & pTypeID, compoent_ptr & pComponent ) noexcept = 0;

		/**
		 * Remove specific Component.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Component Type-ID.
		 * @param pID - Component ID.
		 * @throws - no exceptions.
		**/
		virtual void removeComponent( const TypeID & pTypeID, const ObjectID & pID ) noexcept = 0;

		// -----------------------------------------------------------

	}; // mecs::System

	// -----------------------------------------------------------

} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

#ifndef MECS_SYSTEM_DECL
#define MECS_SYSTEM_DECL
using mecs_System = mecs::System;
#endif // !MECS_SYSTEM_DECL

// -----------------------------------------------------------

#endif // !MECS_SYSTEM_HPP