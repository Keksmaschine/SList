/**
 * @file List.hpp
 * @date 12.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef LIST_HPP
#define LIST_HPP


/**
 * @enum ListIterationAction
 * Actions for the lists iterate methods after a callback function was called for the current element of the iteration.
 * They can be bitwise OR'ed.
 * @var ListIterationAction::ACTION_CONTINUE
 * Continue the iteration. This is the default action.
 * @var ListIterationAction::ACTION_REMOVE
 * Remove the current element.
 * @var ListIterationAction::ACTION_BREAK
 * Abort the iteration.
 */
enum ListIterationAction : unsigned char
{
	ACTION_CONTINUE	= 0x00,
	ACTION_REMOVE	= 0x01,
	ACTION_BREAK	= 0x02
};


/**
 * @class List
 * A double-linked list class. It provides methods similar to the class std::list of the STL.
 * IMPORTANT: Do not declare methods that you want to override in the derived class SList as const. It would change the
 * methods signature and therefore break the inheritance. The derived class SList does change its state on every function call.
 */
template<typename T>
class List
{
private:
	/**
	 * @class Node
	 * Class for nodes of the list. They contain the actual elements of the list as well as pointers to the previous
	 * and next nodes in the list.
	 */
	struct Node
	{
		// Previous node of the list
		Node*	m_prev;
		// Next node of the list
		Node*	m_next;
		// Element of the node
		T		m_element;

		/**
		 * Constructor for instances of the class Node.
		 * @param	element	Element of the node
		 */
		Node(const T& element) : m_prev(nullptr), m_next(nullptr), m_element(element) {}
	};

	// First node of the list
	Node*	m_first;
	// Last node of the list
	Node*	m_last;
	// Count of elements in the list
	size_t	m_size;

	/**
	 * Removes a node from the list.
	 * @param	node	Node to remove from the list
	 */
	void remove(Node* node);

	/**
	 * Clears the list and creates a deep copy of another list.
	 * @param	other	List to copy
	 */
	void copy(const List<T>& other);

	/**
	 * Clears the list and adds the values of an array to the list.
	 * @param	arr	Array to copy
	 */
	template<size_t N>
	void copy(const T (&arr)[N]);

	/**
	 * Checks if the elements of the list are equal to the elements of another list and if they are sorted in the same
	 * order.
	 * @param	other	List to compare to
	 * @return			true if the lists contain equal elements in the same order, false otherwise
	 */
	bool equals(const List<T>& other) const;

public:
	/**
	 * Default constructor for instances of the class List.
	 */
	List();

	/**
	 * Copy-constructor for instances of the class List.
	 * @param	other	List to copy
	 */
	List(const List<T>& other);

	/**
	 * Constructor which creates an instance of the class List from an array.
	 * @param	arr	Array to copy elements from
	 */
	template<size_t N>
	List(const T (&arr)[N]);

	/**
	 * Destructor for instances of the class List.
	 */
	virtual ~List();

	/**
	 * Returns the count of elements in the list.
	 * @return	The count of elements in the list
	 */
	virtual size_t size();

	/**
	 * Checks if the list is empty (= does not contain any elements).
	 * @return	true if the list is empty, otherwise false
	 */
	virtual bool empty();

	/**
	 * Removes all elements from the list.
	 */
	virtual void clear();

	/**
	 * Adds an element to the back of the list.
	 * @param	element	Element to add to the list
	 */
	virtual void push_back(const T& element);

	/**
	 * Adds an element to the front of the list.
	 * @param	element	Element to add to the list
	 */
	virtual void push_front(const T& element);

	/**
	 * Returns a copy of the last element and removes it from the list.
	 * @return	A copy of the removed last element
	 */
	virtual T pop_back();

	/**
	 * Returns a copy of the first element and removes it from the list.
	 * @return	A copy of the removed first element
	 */
	virtual T pop_front();

	/**
	 * Removes elements from the list.
	 * @param	element	Element to remove from the list
	 */
	virtual void remove(const T& element);

	/**
	 * Function pointer to pass to the iterate method for usage as callback function for every element in the list.
	 * @param	element		Current element of the iteration
	 * @param	parameter	A user-defined parameter
	 * @return				Action for the iterate method after calling the callback function. It can be one or more
	 *						values of the ListIterationAction enumeration
	 */
	typedef ListIterationAction (*IterationFunction)(T& element, void* parameter);

	/**
	 * Iterates from the front to the back of the list using a function pointer as callback function for every element
	 * in the list.
	 * @param	func		Pointer to a callback function called for every element in the list
	 * @param	parameter	A user-defined parameter to be passed to the callback function, can be NULL
	 */
	virtual void iterate(const typename List<T>::IterationFunction& func, void* parameter = nullptr);

	/**
	 * Iterates from the front to the back of the list using a lambda function as callback function for every element
	 * in the list. In advance to the iterate method taking a function pointer as parameter this method allows you to
	 * use lambda captures. The callback lambda function should have the following signature:
	 * auto func = [your lambda capture list goes here](T& element) -> ListInterationAction { your code goes here };
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
	virtual List& operator=(const List<T>& other);

	/**
	 * Checks if the elements of the list are equal to the elements of another list and if they are sorted in the same
	 * order.
	 * @param	other	List to compare to
	 * @return			true if the lists contain equal elements in the same order, false otherwise
	 */
	virtual bool operator==(const List<T>& other);

	/**
	 * Checks if the elements of the list are unequal to the elements of another list or if they are sorted in a different
	 * order.
	 * @param	other	List to compare to
	 * @return			true if the lists contain unequal elements or if they are sorted in a different order,
	 *					false otherwise
	 */
	virtual bool operator!=(const List<T>& other);
};


// Include implementation of List
#include "List.tpp"


#endif // #ifndef LIST_HPP
