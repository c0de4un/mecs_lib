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
#ifndef MECS_EVENTS_MANAGER_HPP
#include "EventsManager.hpp"
#endif // !MECS_EVENTS_MANAGER_HPP

// Include mecs::Event
#ifndef MECS_EVENT_HPP
#include "Event.hpp"
#endif // !MECS_EVENT_HPP

// Include mecs::IEventListener
#ifndef MECS_I_EVENT_LISTENER_HPP
#include "IEventListener.hxx"
#endif // !MECS_I_EVENT_LISTENER_HPP

// ===========================================================
// mecs::EventsManager
// ===========================================================

namespace mecs
{

	// -----------------------------------------------------------

	// ===========================================================
	// FIELDS
	// ===========================================================

	/** EventsManager instance. **/
	EventsManager * EventsManager::mInstance( nullptr );

	// ===========================================================
	// CONSTRUCTOR
	// ===========================================================

	/**
	 * EventsManager constructor.
	 *
	 * @throws - no exceptions.
	**/
	EventsManager::EventsManager( ) noexcept
#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		: mEventsMutex( ),
		mEventsQueueMutex( ),
		mEventListenersMutex( ),
		mEvents( ),
#else // ONE-THREAD
		: mEvents( ),
#endif // MULTI-THREADING
		mEventsQueue( ),
		mEventListeners( )
	{
	}

	// ===========================================================
	// DESTRUCTOR
	// ===========================================================

	/**
	 * EventsManager destructor.
	 *
	 * @throws - no exceptions.
	**/
	EventsManager::~EventsManager( ) noexcept = default;

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
	EventsManager::event_listener_ptr_t EventsManager::getNextEventListener( const TypeID & pTypeID, const ObjectID & pIndex ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventListenersMutex );
#endif // MULTI-THREADING

		// Search IEventListeners queue.
		auto queuePos_ = mInstance->mEventListeners.find( pTypeID );

		// Cancel
		if ( queuePos_ == mInstance->mEventListeners.cend( ) )
			return( event_listener_ptr_t( nullptr ) );

		// IEventListeners queue.
		event_listeners_queue_t & queue_lr = queuePos_->second;

		// Cancel
		if ( pIndex >= queue_lr.size( ) )
			return( event_listener_ptr_t( nullptr ) );

		// Get IEventListener
		return( queue_lr.at( pIndex ) ); // Copy-construct.

	}

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
	EventsManager::event_ptr_t EventsManager::getNextEvent( ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventsQueueMutex );
#endif // MULTI-THREADING

		// Cancel, if Events queue is empty.
		if ( mInstance->mEventsQueue.empty( ) )
			return( event_ptr_t( nullptr ) );

		// Get Event
		event_ptr_t event_sp( mInstance->mEventsQueue.front( ) ); // Copy-construct.
		
		// Remove Event from queue.
		mInstance->mEventsQueue.pop_front( );

		// Return Event
		return( event_sp ); // Copy-construct.

	}

	/**
	 * Search for available (for sending) Event.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Event Type-ID.
	 * @return - Event, or null.
	 * @throws - no exceptions.
	**/
	EventsManager::event_ptr_t EventsManager::getEvent( const TypeID & pTypeID ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventsMutex );
#endif // MULTI-THREADING

		// Get Events cache.
		events_vectr_t & eventsCache_lr = mInstance->mEvents[pTypeID];

		// Cancel, if cache is empty.
		if ( eventsCache_lr.empty( ) )
			return( event_ptr_t( nullptr ) );

		// Get Event
		event_ptr_t event_sp( eventsCache_lr.back( ) ); // Copy-construct.

		// Remove Event from cache.
		eventsCache_lr.pop_back( );

		// Return Event.
		return( event_sp ); // Copy-construct.

	}

	// ===========================================================
	// METHODS
	// ===========================================================

	/**
	 * Initialize EventsManager.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void EventsManager::Initialize( ) noexcept
	{

		// Cancel
		if ( mInstance != nullptr )
			return;

		// Create EventsManager instance.
		mInstance = new EventsManager( );

	}

	/**
	 * Terminate EventsManager.
	 *
	 * @thread_safety - not thread-safe.
	 * @throws - no exceptions.
	**/
	void EventsManager::Terminate( ) noexcept
	{

		// Cancel
		if ( mInstance == nullptr )
			return;

		// Delete EventsManager instance.
		delete mInstance;
		mInstance = nullptr;

	}

	/**
	 * Add Event to cache.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pEvent - Event.
	 * @throws - no exceptions.
	**/
	void EventsManager::cacheEvent( event_ptr_t & pEvent ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventsMutex );
#endif // MULTI-THREADING

		// Get Events cache.
		events_vectr_t & eventsCache_lr = mInstance->mEvents[pEvent->mTypeID];

		// Add Event
		eventsCache_lr.push_back( pEvent );

	}

	/**
	 * Send Event now.
	 *
	 * @thread_safety - lock-free, but thread-safe.
	 * @param pEvent - Event to send.
	 * @param pCache - 'true' to store Event after sending & handling.
	 * @throws - no exceptions.
	**/
	void EventsManager::sendEventNow( event_ptr_t & pEvent, const bool pCache ) noexcept
	{

		// IEventListener index.
		ObjectID eventListenerIndex_( 0 );

		// Get first IEventListener.
		event_listener_ptr_t eventListener_( getNextEventListener( pEvent->mTypeID, eventListenerIndex_ ) );

		// Handle Event
		while ( eventListener_ != nullptr )
		{

			// Handle Event
			if ( eventListener_->onEvent( pEvent ) )
				break;

			// Increase IEventListener index.
			eventListenerIndex_++;

			// Next IEventListener
			eventListener_ = getNextEventListener( pEvent->mTypeID, eventListenerIndex_ );

		} // Handle Event

		// Cache Event
		if ( pCache )
			cacheEvent( pEvent );

	}

	/**
	 * Add Event to queue.
	 *
	 * @thread_safety - lock-free, but thread-safe.
	 * @param pEvent - Event.
	 * @throws - no exceptions.
	**/
	void EventsManager::sendEvent( event_ptr_t & pEvent ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventsQueueMutex );
#endif // MULTI-THREADING

		// Add Event to queue.
		mInstance->mEventsQueue.push_back( pEvent );

	}

	/**
	 * Send all Events from queue.
	 *
	 * @thread_safety - lock-free, but thread-safe.
	 * @throws - no exceptions.
	**/
	void EventsManager::sendEvents( ) noexcept
	{

		// Get Event
		event_ptr_t event_sp( getNextEvent( ) );

		// Cancel
		if ( event_sp == nullptr )
			return;

		// Handle Events
		while ( event_sp != nullptr )
		{

			// IEventListener index.
			ObjectID eventListenerIndex_( 0 );

			// Get IEventListener
			event_listener_ptr_t eventLsitener_sp( getNextEventListener( event_sp->mTypeID, eventListenerIndex_ ) );

			// Handle Event
			while ( eventLsitener_sp != nullptr )
			{

				// Handle Event
				if ( eventLsitener_sp->onEvent( event_sp ) )
				{

					// Cache Event
					cacheEvent( event_sp );

					// Stop
					break;

				}

				// Increase IEventListener index.
				eventListenerIndex_++;

				// Next IEventListener
				event_listener_ptr_t eventLsitener_sp = getNextEventListener( event_sp->mTypeID, eventListenerIndex_ );

			} // Handle Event

			// Get next Event
			event_sp = getNextEvent( );

		} // Handle Events

	}

	/**
	 * Add IEventListener.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Event Type-ID.
	 * @param pListener - IEventListener.
	 * @throws - no exceptions.
	**/
	void EventsManager::registerEventListener( const TypeID & pTypeID, event_listener_ptr_t & pListener ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventListenersMutex );
#endif // MULTI-THREADING

		// Get Event Listeners container.
		event_listeners_queue_t & listenersQueue_lr = mInstance->mEventListeners[pTypeID];

		// Add Event Listener.
		listenersQueue_lr.push_back( pListener ); // Copy-construct.

	}

	/**
	 * Removes IEventListener.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Event Type-ID.
	 * @param pListener - IEventListener.
	 * @throws - no exceptions.
	**/
	void EventsManager::unregisterEventListener( const TypeID & pTypeID, event_listener_ptr_t & pListener ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventListenersMutex );
#endif // MULTI-THREADING

		// Search IEventListeners queue.
		auto queuePos_ = mInstance->mEventListeners.find( pTypeID );

		// Cancel
		if ( queuePos_ == mInstance->mEventListeners.cend( ) )
			return;

		// IEventListeners queue.
		event_listeners_queue_t & eventListeners_lr = queuePos_->second;

		// IEventListeners iterator.
		auto queueIter_ = eventListeners_lr.begin( );

		// IEventListeners queue end-iterator.
		auto queueEndIter_ = eventListeners_lr.cend( );

		// Search IEventListener
		while ( queueIter_ != queueEndIter_ )
		{

			// Check pointers-values (address).
			if ( pListener == *queueIter_ )
			{

				// Swap
				std::swap( *queueIter_, eventListeners_lr.back( ) );

				// Remove
				eventListeners_lr.pop_back( );

				// Stop
				return;

			}

			// Next IEventListener
			queueIter_++;

		}

	}

	/**
	 * Remove all cached Events.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Event Type-ID.
	 * @throws - no exceptions.
	**/
	void EventsManager::clearEvents( const TypeID & pTypeID ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventsMutex );
#endif // MULTI-THREADING

		// Search Events cache.
		auto eventsCacheIter_ = mInstance->mEvents.find( pTypeID );

		// Cancel, if not found.
		if ( eventsCacheIter_ == mInstance->mEvents.cend( ) )
			return;

		// Remove Events from cache.
		mInstance->mEvents.erase( eventsCacheIter_ );

	}

	/**
	 * Remove all IEventListeners.
	 *
	 * @thread_safety - thread-lock used.
	 * @param pTypeID - Event Type-ID.
	 * @throws - no exceptions.
	**/
	void EventsManager::clearEventListeners( const TypeID & pTypeID ) noexcept
	{

#ifdef MECS_LIB_MT_ENABLED // MULTI-THREADING
		// Lock
		mecs_ulock lock_( mInstance->mEventListenersMutex );
#endif // MULTI-THREADING

		// Search IEventListeners queue.
		auto queuePos_ = mInstance->mEventListeners.find( pTypeID );

		// Cancel
		if ( queuePos_ == mInstance->mEventListeners.cend( ) )
			return;

		// Remove IEventListeners
		mInstance->mEventListeners.erase( queuePos_ );

	}

	// -----------------------------------------------------------

} // mecs

// -----------------------------------------------------------