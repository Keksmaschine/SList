/**
 * @file Mutex.cpp
 * @date 12.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#include "Mutex.hpp"

Mutex::Mutex()
{
#ifdef __linux__
	// Initialize mutex attribute
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	// Initialize the mutex
	pthread_mutex_init(&m_mutex, &attr);
	// Uninitialize mutex attribute
	pthread_mutexattr_destroy(&attr);
#elif defined(_WIN32)
	InitializeCriticalSection(static_cast<LPCRITICAL_SECTION>(&m_section));
#endif
}

Mutex::~Mutex()
{
#ifdef __linux__
	pthread_mutex_destroy(&m_mutex);
#elif defined(_WIN32)
	DeleteCriticalSection(static_cast<LPCRITICAL_SECTION>(&m_section));
#endif
}

void Mutex::lock()
{
#ifdef __linux__
	pthread_mutex_lock(&m_mutex);
#elif defined(_WIN32)
	EnterCriticalSection(static_cast<LPCRITICAL_SECTION>(&m_section));
#endif
}

void Mutex::unlock()
{
#ifdef __linux__
	pthread_mutex_unlock(&m_mutex);
#elif defined(_WIN32)
	LeaveCriticalSection(static_cast<LPCRITICAL_SECTION>(&m_section));
#endif
}

bool Mutex::try_lock()
{
#ifdef __linux__
	return (0 == pthread_mutex_trylock(&m_mutex));
#elif defined(_WIN32)
	return (0 != TryEnterCriticalSection(static_cast<LPCRITICAL_SECTION>(&m_section)));
#endif
}
