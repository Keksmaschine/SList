/**
 * @file SList.tpp
 * @date 12.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef SLIST_HPP
#error SLIST_HPP undefined
#endif

template<typename T>
SList<T>::SList() : m_mutex()
{
	// Nothing to do yet
}

template<typename T>
SList<T>::SList(const List<T>& other) : List<T>(other), m_mutex()
{
	// Nothing to do yet
}

template<typename T>
template<size_t N>
SList<T>::SList(const T (&other)[N]) : List<T>(other), m_mutex()
{
	// Nothing to do yet
}

template<typename T>
SList<T>::~SList()
{
	// Nothing to do yet
}

template<typename T>
bool SList<T>::empty()
{
	m_mutex.lock();
	bool ret = List<T>::empty();
	m_mutex.unlock();
	return ret;
}

template<typename T>
void SList<T>::clear()
{
	m_mutex.lock();
	List<T>::clear();
	m_mutex.unlock();
}

template<typename T>
size_t SList<T>::size()
{
	m_mutex.lock();
	size_t size = List<T>::size();
	m_mutex.unlock();
	return size;
}

template<typename T>
void SList<T>::push_back(const T& element)
{
	m_mutex.lock();
	List<T>::push_back(element);
	m_mutex.unlock();
}

template<typename T>
void SList<T>::push_front(const T& element)
{
	m_mutex.lock();
	List<T>::push_front(element);
	m_mutex.unlock();
}

template<typename T>
T SList<T>::pop_back()
{
	m_mutex.lock();
	T element = List<T>::pop_back();
	m_mutex.unlock();
	return element;
}

template<typename T>
T SList<T>::pop_front()
{
	m_mutex.lock();
	T element = List<T>::pop_front();
	m_mutex.unlock();
	return element;
}

template<typename T>
void SList<T>::remove(const T& element)
{
	m_mutex.lock();
	List<T>::remove(element);
	m_mutex.unlock();
}

template<typename T>
void SList<T>::iterate(const typename List<T>::IterationFunction& func, void* parameter)
{
	m_mutex.lock();
	List<T>::iterate(func, parameter);
	m_mutex.unlock();
}

template<typename T>
template<typename Lambda>
void SList<T>::iterate(const Lambda& func)
{
	m_mutex.lock();
	List<T>::iterate(func);
	m_mutex.unlock();
}

template<typename T>
SList<T>& SList<T>::operator=(const List<T>& other)
{
	m_mutex.lock();
	List<T>::operator=(other);
	m_mutex.unlock();
	return *this;
}

template<typename T>
bool SList<T>::operator==(const List<T>& other)
{
	m_mutex.lock();
	bool ret = List<T>::operator==(other);
	m_mutex.unlock();
	return ret;
}

template<typename T>
bool SList<T>::operator!=(const List<T>& other)
{
	m_mutex.lock();
	bool ret = List<T>::operator!=(other);
	m_mutex.unlock();
	return ret;
}
