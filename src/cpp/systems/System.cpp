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
#ifndef MECS_SYSTEM_HPP
#include "System.hpp"
#endif // !MECS_SYSTEM_HPP

// Include mecs::Component
#ifndef MECS_COMPONENT_HPP
#include "../components/Component.hpp"
#endif // !MECS_COMPONENT_HPP

// ===========================================================
// mecs::System
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	 * System constructor.
	 *
	 * @param pTypeID - System Type-ID.
	 * @throws - no exceptions.
	**/
	System::System( const TypeID & pTypeID ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		: mMutex( ),
		mEnabled( false ),
#else // ONE-THREAD
		: mEnabled( false ),
#endif // MULTI-THREADING
		mTypeID( pTypeID )
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	 * System destructor.
	 *
	 * @throws - no exceptions.
	**/
	System::~System( ) noexcept = default;

	// ===========================================================
	// GETTERS & SETTERS
	// ===========================================================

	/**
	 * Returns 'true' if this System is Enabled.
	 *
	 * @thread_safety - atomic-flag used.
	 * @throws - no exceptions.
	**/
	bool System::isEnabled( ) const noexcept
	{ return( mEnabled ? true : false ); }

	// -----------------------------------------------------------

} // mecs

// -----------------------------------------------------------