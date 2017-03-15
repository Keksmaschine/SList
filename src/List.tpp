/**
 * @file List.tpp
 * @date 12.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef LIST_HPP
#error LIST_HPP undefined
#endif

template<typename T>
void List<T>::remove(Node* node)
{
	if (node->m_prev)
	{
		node->m_prev->m_next = node->m_next;
	}
	else
	{
		// node is m_fist, set new m_first to node->m_next
		m_first = node->m_next;
	}

	if (node->m_next)
	{
		node->m_next->m_prev = node->m_prev;
	}
	else
	{
		// node is m_last, set new m_last to node->m_prev
		m_last = node->m_prev;
	}

	delete node;
	m_size--;
}

template<typename T>
void List<T>::copy(const List<T>& other)
{
	if (this != &other)
	{
		clear();
		// Prefer a function pointer over a lambda function in order to guarantee thread-safety of the derived class SList
		IterationFunction copyList = [](T& element, void* parameter) -> ListIterationAction
		{
			(static_cast<List*>(parameter))->push_back(element);
			return ListIterationAction::ACTION_CONTINUE;
		};
		(const_cast<List&>(other)).iterate(copyList, static_cast<void*>(this));
	}
}

template<typename T>
template<size_t N>
void List<T>::copy(const T (&arr)[N])
{
	clear();
	for (size_t i = 0; i < N; i++)
	{
		push_back(arr[i]);
	}
}

template<typename T>
bool List<T>::equals(const List<T>& other) const
{
	if (this == &other)
	{
		return true;
	}

	bool ret = false;
	//if (other.size() == m_size) // Refrain from this check in order to guarantee thread-safety of the derived class SList
	{
		// Prepare parameters
		struct ComparisionParams
		{
			Node*	m_current;
			size_t	m_countOfEqualElements;
			size_t	m_countOfComparedElements;
		} params;
		params.m_current					= m_first;
		params.m_countOfEqualElements		= 0;
		params.m_countOfComparedElements	= 0;

		IterationFunction compare = [](T& element, void* parameter) -> ListIterationAction
		{
			ComparisionParams* params = static_cast<ComparisionParams*>(parameter);
			// Compare current elements
			if (params->m_current && params->m_current->m_element == element)
			{
				// Increase the count of equal elements and count of compared elements
				params->m_countOfEqualElements++;
				params->m_countOfComparedElements++;
				// Get the next node of our list
				params->m_current = params->m_current->m_next;
				// Continue the iteration
				return ListIterationAction::ACTION_CONTINUE;
			}
			// Current element is unequal or our list contains less elements the the other list, break the iteration
			params->m_countOfComparedElements++;
			return ListIterationAction::ACTION_BREAK;
		};

		// Iterate the list using the compare function pointer as callback for the iteration
		(const_cast<List&>(other)).iterate(compare, &params);

		// If the count of equal elements is equal to the size of the list, return true
		if (m_size == params.m_countOfComparedElements && params.m_countOfComparedElements == params.m_countOfEqualElements)
		{
			ret = true;
		}
	}
	return ret;
}

template<typename T>
List<T>::List() : m_first(nullptr), m_last(nullptr), m_size(0)
{
	// Nothing to do yet
}

template<typename T>
List<T>::List(const List<T>& other) : m_first(nullptr), m_last(nullptr), m_size(0)
{
	copy(other);
}

template<typename T>
template<size_t N>
List<T>::List(const T (&other)[N]) : m_first(nullptr), m_last(nullptr), m_size(0)
{
	copy(other);
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
size_t List<T>::size()
{
	return m_size;
}

template<typename T>
bool List<T>::empty()
{
	return 0 == m_size;
}

template<typename T>
void List<T>::clear()
{
	Node* current = m_first;
	while (current)
	{
		Node* next = current->m_next;
		delete current;
		current = next;
	}
	m_first = nullptr;
	m_last = nullptr;
	m_size = 0;
}

template<typename T>
void List<T>::push_back(const T& element)
{
	Node* newnode = new Node(element);
	if (m_first)
	{
		// List is not empty
		newnode->m_prev = m_last;
		m_last->m_next = newnode;
		m_last = newnode;
	}
	else
	{
		// List is empty
		m_first = newnode;
		m_last = newnode;
	}
	m_size++;
}

template<typename T>
void List<T>::push_front(const T& element)
{
	Node* newnode = new Node(element);
	if (m_first)
	{
		// List is not empty
		newnode->m_next = m_first;
		m_first->m_prev = newnode;
		m_first = newnode;
	}
	else
	{
		// List is empty
		m_first = newnode;
		m_last = newnode;
	}
	m_size++;
}

template<typename T>
T List<T>::pop_back()
{
	if (m_last)
	{
		T element = m_last->m_element;
		remove(m_last);
		return element;
	}
	return T(0);
}

template<typename T>
T List<T>::pop_front()
{
	if (m_first)
	{
		T element = m_first->m_element;
		remove(m_first);
		return element;
	}
	return T(0);
}

template<typename T>
void List<T>::remove(const T& element)
{
	Node* current = m_first;
	while (current)
	{
		Node* next = current->m_next;
		if (element == current->m_element)
		{
			remove(current);
		}
		current = next;
	}
}

template<typename T>
void List<T>::iterate(const typename List<T>::IterationFunction& func, void* parameter)
{
	Node* current = m_first;
	while (current)
	{
		Node* next = current->m_next;
		ListIterationAction action = func(current->m_element, parameter);
		if (action & ListIterationAction::ACTION_REMOVE)
		{
			remove(current);
		}
		if (action & ListIterationAction::ACTION_BREAK)
		{
			break;
		}
		current = next;
	}
}

template<typename T>
template<typename Lambda>
void List<T>::iterate(const Lambda& func)
{
	Node* current = m_first;
	while (current)
	{
		Node* next = current->m_next;
		ListIterationAction action = func(current->m_element);
		if (action & ListIterationAction::ACTION_REMOVE)
		{
			remove(current);
		}
		if (action & ListIterationAction::ACTION_BREAK)
		{
			break;
		}
		current = next;
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	copy(other);
	return *this;
}

template<typename T>
bool List<T>::operator==(const List<T>& other)
{
	return equals(other);
}

template<typename T>
bool List<T>::operator!=(const List<T>& other)
{
	return !equals(other);
}
