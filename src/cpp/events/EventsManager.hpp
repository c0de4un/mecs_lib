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

#ifndef MECS_EVENTS_MANAGER_HPP
#define MECS_EVENTS_MANAGER_HPP

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
	// mecs::EventsManager
	// ===========================================================

	/**
	 * EventsManager - manage & stores Events.
	 * 
	 * @authors Denis Z. (code4un@yandex.ru)
	 * @version 1.0
	 * @since 21.03.2019
	**/
	class EventsManager final
	{

	private:

		// -----------------------------------------------------------

		// ===========================================================
		// CONFIGS
		// ===========================================================

		/** Type-alias for Event pointer. **/
		using event_ptr_t = mecs_shared<Event>;

		/** Type-alias for Events vector. **/
		using events_vectr_t = mecs_vector<event_ptr_t>;

		/** Type-alias for Events map. **/
		using events_map_t = mecs_map<const TypeID, events_vectr_t>;

		/** Type-alias for IEventListener pointer. **/
		using event_listener_ptr_t = mecs_shared<IEventListener>;

		/** Type-alias for IEventListeners queue. **/
		using event_listeners_queue_t = mecs_vector<event_listener_ptr_t>;

		/** Type-alias for IEventListeners_map. **/
		using event_listeners_map_t = mecs_map<const TypeID, event_listeners_queue_t>;

		/** Type-alias for Events deque. **/
		using events_queue_t = mecs_deque<event_ptr_t>;

		// ===========================================================
		// FIELDS
		// ===========================================================

		/** EventsManager instance. **/
		static EventsManager * mInstance;

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		/** Events Mutex. **/
		mecs_mutex mEventsMutex;

		/** Events Queue Mutex. **/
		mecs_mutex mEventsQueueMutex;

		/** IEventListeners Mutex. **/
		mecs_mutex mEventListenersMutex;
#endif // MULTI-THREADING

		/** Events map. **/
		events_map_t mEvents;

		/** Events Queue. **/
		events_queue_t mEventsQueue;

		/** IEventListeners map. **/
		event_listeners_map_t mEventListeners;

		// ===========================================================
		// CONSTRUCTOR
		// ===========================================================

		/**
		 * EventsManager constructor.
		 *
		 * @throws - no exceptions.
		**/
		explicit EventsManager( ) noexcept;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		 * Returns next IEventListener in queue, or null.
		 * 
		 * (?) Used instead of iteration while locked, to avoid self-lock
		 * & reduce wait-time.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Event Type-ID.
		 * @param pIndex - index. 0 to get first IEventListener in queue.
		 * @return - IEventListener, or null.
		 * @throws - no exceptions.
		**/
		static event_listener_ptr_t getNextEventListener( const TypeID & pTypeID, const ObjectID & pIndex ) noexcept;

		/**
		 * Returns next Event in queue, or null.
		 * 
		 * (?) Used instead of iteration while locked, to avoid self-lock
		 * & reduce wait-time.
		 *
		 * @thread_safety - thread-lock used.
		 * @return - Event, or null.
		 * @throws - no exceptions.
		**/
		static event_ptr_t getNextEvent( ) noexcept;

		// ===========================================================
		// DELETED
		// ===========================================================

		/* @deleted EventsManager const copy constructor */
		EventsManager( const EventsManager & ) = delete;

		/* @deleted EventsManager const copy assignment operator */
		EventsManager & operator=( const EventsManager & ) = delete;

		/* @deleted EventsManager move constructor */
		EventsManager( EventsManager && ) = delete;

		/* @deleted EventsManager move assignment operator */
		EventsManager & operator=( EventsManager && ) = delete;

		// -----------------------------------------------------------

	public:

		// -----------------------------------------------------------

		// ===========================================================
		// DESTRUCTOR
		// ===========================================================

		/**
		 * EventsManager destructor.
		 *
		 * @throws - no exceptions.
		**/
		~EventsManager( ) noexcept;

		// ===========================================================
		// GETTERS & SETTERS
		// ===========================================================

		/**
		 * Search for available (for sending) Event.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Event Type-ID.
		 * @return - Event, or null.
		 * @throws - no exceptions.
		**/
		static event_ptr_t getEvent( const TypeID & pTypeID ) noexcept;

		// ===========================================================
		// METHODS
		// ===========================================================

		/**
		 * Initialize EventsManager.
		 *
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Initialize( ) noexcept;

		/**
		 * Terminate EventsManager.
		 *
		 * @thread_safety - not thread-safe.
		 * @throws - no exceptions.
		**/
		static void Terminate( ) noexcept;

		/**
		 * Add Event to cache.
		 *
		 * @thread_safety - thread-lock used.
		 * @param pEvent - Event.
		 * @throws - no exceptions.
		**/
		static void cacheEvent( event_ptr_t & pEvent ) noexcept;

		/**
		 * Send Event now.
		 * 
		 * @thread_safety - lock-free, but thread-safe.
		 * @param pEvent - Event to send.
		 * @param pCache - 'true' to store Event after sending & handling.
		 * @throws - no exceptions.
		**/
		static void sendEventNow( event_ptr_t & pEvent, const bool pCache ) noexcept;

		/**
		 * Add Event to queue.
		 *
		 * @thread_safety - lock-free, but thread-safe.
		 * @param pEvent - Event.
		 * @throws - no exceptions.
		**/
		static void sendEvent( event_ptr_t & pEvent ) noexcept;

		/**
		 * Send all Events from queue.
		 * 
		 * @thread_safety - lock-free, but thread-safe.
		 * @throws - no exceptions.
		**/
		static void sendEvents( ) noexcept;

		/**
		 * Add IEventListener.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Event Type-ID.
		 * @param pListener - IEventListener.
		 * @throws - no exceptions.
		**/
		static void registerEventListener( const TypeID & pTypeID, event_listener_ptr_t & pListener ) noexcept;

		/**
		 * Removes IEventListener.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Event Type-ID.
		 * @param pListener - IEventListener.
		 * @throws - no exceptions.
		**/
		static void unregisterEventListener( const TypeID & pTypeID, event_listener_ptr_t & pListener ) noexcept;

		/**
		 * Remove all cached Events.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Event Type-ID.
		 * @throws - no exceptions.
		**/
		static void clearEvents( const TypeID & pTypeID ) noexcept;

		/**
		 * Remove all IEventListeners.
		 * 
		 * @thread_safety - thread-lock used.
		 * @param pTypeID - Event Type-ID.
		 * @throws - no exceptions.
		**/
		static void clearEventListeners( const TypeID & pTypeID ) noexcept;

		// -----------------------------------------------------------

	}; // mecs::EventsManager

	// -----------------------------------------------------------

} // mecs

// ===========================================================
// CONFIGS
// ===========================================================

#ifndef MECS_EVENTS_MANAGER_DECL
#define MECS_EVENTS_MANAGER_DECL
using mecs_EventsManager = mecs::EventsManager;
#endif // !MECS_EVENTS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !MECS_EVENTS_MANAGER_HPP