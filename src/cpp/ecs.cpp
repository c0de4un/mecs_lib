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
#ifndef MECS_ECS_HPP
#include "ecs.hpp"
#endif // !MECS_ECS_HPP

// Include mecs::ComponentsManager
#ifndef MECS_COMPONENTS_MANAGER_HPP
#include "components/ComponentsManager.hpp"
#endif // !MECS_COMPONENTS_MANAGER_HPP

// Include mecs::EntitiesManager
#ifndef MECS_ENTITiES_MANAGER_HPP
#include "entities/EntitiesManager.hpp"
#endif // !MECS_ENTITiES_MANAGER_HPP

// Include mecs::SystemsManager
#ifndef MECS_SYSTEMS_MANAGER_HPP
#include "systems/SystemsManager.hpp"
#endif // !MECS_SYSTEMS_MANAGER_HPP

// Include mecs::EventsManager
#ifndef MECS_EVENTS_MANAGER_HPP
#include "events/EventsManager.hpp"
#endif // !MECS_EVENTS_MANAGER_HPP

// ===========================================================
// IMPLEMENTATION
// ===========================================================

namespace mecs
{
	
	// -----------------------------------------------------------
	
	// ===========================================================
	// METHODS
	// ===========================================================
	
	/**
	 * Initialize.
	 * 
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/ 
	void ECSEngine::Initialize( ) noexcept
	{
		
		// Initialize ComponentsManager
		ComponentsManager::Initialize( );
		
		// Initialize EntitiesManager
		EntitiesManager::Initialize( );

		// Initialize SystemsManager
		SystemsManager::Initialize( );

		// Initialize EventsManager
		EventsManager::Initialize( );

	}
	
	/**
	 * Terminate.
	 * 
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/ 
	void ECSEngine::Terminate( ) noexcept
	{
		
		// Terminate ComponentsManager
		ComponentsManager::Terminate( );
		
		// Terminate EntitiesManager
		EntitiesManager::Terminate( );

		// Terminate SystemsManager
		SystemsManager::Terminate( );

		// Terminate EventsManager
		EventsManager::Terminate( );

	}
	
	// -----------------------------------------------------------
	
} // mecs

// -----------------------------------------------------------