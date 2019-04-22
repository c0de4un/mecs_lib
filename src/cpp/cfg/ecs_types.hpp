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

#ifndef MECS_TYPES_HPP
#define MECS_TYPES_HPP

// -----------------------------------------------------------

// ===========================================================
// @about
// This header contains configuration for types used by
// 'mecs' namespace.
// ===========================================================

// ===========================================================
// INCLUDES
// ===========================================================

// Include C++ memory
#include <memory>

// MULTI-THREADING
#ifdef MECS_LIB_MT_ENABLED

// Include C++ atomic
#include <atomic>

// Include C++ mutex
#include <mutex>

#endif // !MECS_LIB_MT_ENABLED
// MULTI-THREADING

// Include C++ vector
#include <vector>

// Include C++ deque (deck)
#include <deque>

// Include C++ map
#include <map>

// Include C++ definitions
#include <cstddef>

// Include C++ integer-types
#include <cstdint>

// Include C++ limits
#include <limits>

// ===========================================================
// NUMERIC
// ===========================================================

namespace mecs
{
	
	/** Type-ID. **/
	using TypeID = std::uint8_t;
	
	/** Invalid Type-ID. **/
	static constexpr const TypeID INVALID_TYPE_ID = std::numeric_limits<TypeID>::max( ) - 1;
	
	/** Object-ID. **/
	using ObjectID = std::uint16_t;
	
	/** Invalid Object-ID. **/
	static constexpr const TypeID INVALID_OBJECT_ID = std::numeric_limits<ObjectID>::max( ) - 1;
	
	/** Type-alias for shared-pointer. **/
	template <typename T>
	using mecs_shared = std::shared_ptr<T>;
	
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
	
	/** Type-alias for mutex. **/
	using mecs_mutex = std::mutex;
	
	/** Type-alias for unique_lock. **/
	using mecs_ulock = std::unique_lock<mecs_mutex>;
	
	/** Type-alias for atomic-types. **/
	template <typename T>
	using mecs_atomic = std::atomic<T>;
	
	/** Type-alias for atomic-boolean value-type. **/
	using mecs_abool = std::atomic_bool;
	
#endif // MULTI-THREADING
	
	/** Alias for vector container. **/
	template <typename T>
	using mecs_vector = std::vector<T>;
	
	/** Type-alias for map. **/
	template <typename K, typename V>
	using mecs_map = std::map<K, V>;
	
	/** Alias for deque. **/
	template <typename T>
	using mecs_deque = std::deque<T>;

} // mecs

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// mecs::Component
#ifndef MECS_COMPONENT_DECL
#define MECS_COMPONENT_DECL
namespace mecs { struct Component; }
using mecs_Component = mecs::Component;
#endif // !MECS_COMPONENT_DECL

// mecs::ComponentsManager
#ifndef MECS_COMPONENTS_MANAGER_DECL
#define MECS_COMPONENTS_MANAGER_DECL
namespace mecs { class ComponentsManager; }
using mecs_ComponentsManager = mecs::ComponentsManager;
#endif // !MECS_COMPONENTS_MANAGER_DECL

// mecs::Entity
#ifndef MECS_ENTITY_DECL
#define MECS_ENTITY_DECL
namespace mecs { class Entity; }
using mecs_Entity = mecs::Entity;
#endif // !MECS_ENTITY_DECL

// mecs::EntitiesManager
#ifndef MECS_ENTITIES_MANAGER_DECL
#define MECS_ENTITIES_MANAGER_DECL
namespace mecs { class EntitiesManager; }
using mecs_EntitiesManager = mecs::EntitiesManager;
#endif // !MECS_ENTITIES_MANAGER_DECL

// mecs::System
#ifndef MECS_SYSTEM_DECL
#define MECS_SYSTEM_DECL
namespace mecs { class System; }
using mecs_System = mecs::System;
#endif // !MECS_SYSTEM_DECL

// mecs::SystemsManager
#ifndef MECS_SYSTEMS_MANAGER_DECL
#define MECS_SYSTEMS_MANAGER_DECL
namespace mecs { class SystemsManager; }
using mecs_SystemsManager = mecs::SystemsManager;
#endif // !MECS_SYSTEMS_MANAGER_DECL

// mecs::Event
#ifndef MECS_EVENT_DECL
#define MECS_EVENT_DECL
namespace mecs { struct Event; }
using mecs_Event = mecs::Event;
#endif // !MECS_EVENT_DECL

// mecs::EventsManager
#ifndef MECS_EVENTS_MANAGER_DECL
#define MECS_EVENTS_MANAGER_DECL
namespace mecs { class EventsManager; }
using mecs_EventsManager = mecs::EventsManager;
#endif // !MECS_EVENTS_MANAGER_DECL

// mecs::IEventListener
#ifndef MECS_I_EVENT_LISTENER_DECL
#define MECS_I_EVENT_LISTENER_DECL
namespace mecs { class IEventListener; }
using mecs_IEventListener = mecs::IEventListener;
#endif // !MECS_I_EVENT_LISTENER_DECL

// ===========================================================
// ALIASES & TYPEDEFS
// ===========================================================

/** Type-alias for mecs::TypeID. **/
using ecs_TypeID = mecs::TypeID;

/** Type-alias for mecs::ObjectID **/
using ecs_ObjectID = mecs::ObjectID;

// -----------------------------------------------------------

#endif // !MECS_TYPES_HPP