/**
 * @file Mutex.hpp
 * @date 12.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef MUTEX_HPP
#define MUTEX_HPP


#ifdef __linux__
#include <pthread.h>
#elif defined(_WIN32)
#include <windows.h>
#endif


/**
 * @class Mutex
 * Mutex implementation like the std::mutex class of the STL.
 */
class Mutex
{
private:
#ifdef __linux__
	// Mutex object of the Mutex class
	pthread_mutex_t m_mutex;
#elif defined(_WIN32)
	// Critical section object of the Mutex class
	CRITICAL_SECTION m_section;
#endif

public:
	/**
	 * Constructor for instances of the class Mutex.
	 */
	Mutex();

	/**
	 * Destructor for instances of the class Mutex.
	 */
	virtual ~Mutex();

	/**
	 * Blocks until the mutex can be locked. Locks the mutex for the calling thread.
	 */
	void lock();

	/**
	 * Unlocks the mutex.
	 */
	void unlock();

	/**
	 * Tries to lock the mutex. The method returns immediately.
	 * @return	true if the mutex is locked, false otherwise
	 */
	bool try_lock();
};


#endif // #ifndef MUTEX_HPP
