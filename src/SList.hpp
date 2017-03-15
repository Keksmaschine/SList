/**
 * @file SList.hpp
 * @date 12.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef SLIST_HPP
#define SLIST_HPP


#include "List.hpp"
#include "Mutex.hpp"


/**
 * @class SList
 * A thread-safe double-linked list class. It provides methods similar to the class std::list of the STL.
 */
template<typename T>
class SList : public List<T>
{
private:
	// Mutex instance used to lock and unlock the list and to guarantee thread-safety
	Mutex m_mutex;

public:
	/**
	 * Default constructor for instances of the class SList.
	 */
	SList();

	/**
	 * Copy-constructor for instances of the class SList.
	 * @param	other	List to copy
	 */
	SList(const List<T>& other);

	/**
	 * Constructor which creates an instance of the class SList from an array.
	 * @param	arr	Array to copy elements from
	 */
	template<size_t N>
	SList(const T (&other)[N]);

	/**
	 * Destructor for instances of the class SList.
	 */
	virtual ~SList();

	/**
	 * Checks if the list is empty (= does not contain any elements) at the time m_mutex can be locked.
	 * @return	true if the list is empty, otherwise false
	 */
	bool empty();

	/**
	 * Removes all elements from the list.
	 */
	void clear();

	/**
	 * Returns the count of elements in the list at the time m_mutex can be locked.
	 * @return	The count of elements in the list
	 */
	size_t size();

	/**
	 * Adds an element to the back of the list.
	 * @param	element	Element to add to the list
	 */
	void push_back(const T& element);

	/**
	 * Adds an element to the front of the list.
	 * @param	element	Element to add to the list
	 */
	void push_front(const T& element);

	/**
	 * Returns a copy of the last element and removes it from the list.
	 * @return	A copy of the removed last element
	 */
	T pop_back();

	/**
	 * Returns a copy of the first element and removes it from the list.
	 * @return	A copy of the removed first element
	 */
	T pop_front();

	/**
	 * Removes elements from the list.
	 * @param	element	Element to remove from the list
	 */
	void remove(const T& element);

	/**
	 * Iterates from the front to the back of the list using a function pointer as callback function for every element
	 * in the list.
	 * @param	func		Pointer to a callback function called for every element in the list
	 * @param	parameter	A user-defined parameter to be passed to the callback function, it can be NULL
	 */
	void iterate(const typename List<T>::IterationFunction& func, void* parameter = nullptr);

	/**
	 * Iterates from the front to the back of the list using a lambda function as callback function for every element
	 * in the list. In advance to the iterate method taking a function pointer this method allows you to use lambda
	 * captures. The callback lambda function should have the following signature:
	 * auto func = [your lambda capture list goes here](T& element) -> ListInterationAction { your code goes here };
	 * IMPORTANT: If you call this method from a base class pointer or reference thread-safety is not guaranteed since
	 * C++ does not allow virtual template methods and therefore the iterate method of the base class is called.
	 * @param	func	Callback lambda function called for every element in the list. It receives a reference to the
	 *					current element as a parameter.
	 */
	template<typename Lambda>
	void iterate(const Lambda& func);

	/**
	 * Clears the list and creates a deep copy of another list.
	 * @param	other	List to copy
	 * @return			Reference to the List instance
	 */
	SList& operator=(const List<T>& other);

	/**
	 * Checks if the elements of the list are equal to the elements of another list and if they are sorted in the same
	 * order.
	 * IMPORTANT: If you upcast an SList to a List and pass it to this function as a parameter thread-safety of the
	 * comparision is not guaranteed.
	 * @param	other	List to compare to
	 * @return			true if the lists contain equal elements in the same order, false otherwise
	 */
	bool operator==(const List<T>& other);

	/**
	 * Checks if the elements of the list are unequal to the elements of another list or if they are sorted in a different
	 * order.
	 * IMPORTANT: If you upcast an SList to a List and pass it to this function as a parameter thread-safety of the
	 * comparision is not guaranteed.
	 * @param	other	List to compare to
	 * @return			true if the lists contain unequal elements or if they are sorted in a different order,
	 *					false otherwise
	 */
	bool operator!=(const List<T>& other);
};


// Include implementation of SList
#include "SList.tpp"


#endif // #ifndef SLIST_HPP
