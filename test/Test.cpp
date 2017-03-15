#include <iostream>
#include <thread>
#include "../src/List.hpp"
#include "../src/SList.hpp"

/**
 * Prints an error message to the standart error stream if a given expression is false.
 * @param	expression		Expression to test
 * @param	errorMessage	Error message to print to the standart error stream
 */
static void dynamic_assert(const bool expression, const char* errorMessage)
{
	if (!expression)
	{
		std::cerr << errorMessage << std::endl;
	}
}

/**
 * Tests the contructors of List and SList.
 */
static void TestConstructors()
{
	// Test default contructors
	List<int> list1;
	dynamic_assert(0 == list1.size(), "Error in List<T>::List() or List<T>::size method");
	dynamic_assert(list1.empty(), "Error in List<T>::List() or List<T>::empty method");

	SList<int> slist1;
	dynamic_assert(0 == slist1.size(), "Error in SList<T>::SList() or SList<T>::size method");
	dynamic_assert(slist1.empty(), "Error in SList<T>::SList() or SList<T>::empty method");

	const int numbers[] = { 0,1,2,3,4,5,6,7,8,9 };

	// Test constructors which construct a list from an array
	List<int> list2(numbers);
	dynamic_assert(sizeof(numbers) / sizeof(int) == list2.size(), "Error in List<T>::List(const T (&arr)[]) or List<T>::size method");
	dynamic_assert(!list2.empty(), "Error in List<T>::List(const T (&arr)[]) or List<T>::empty method");

	SList<int> slist2(numbers);
	dynamic_assert(sizeof(numbers) / sizeof(int) == slist2.size(), "Error in SList<T>::SList(const T (&arr)[]) or SList<T>::size method");
	dynamic_assert(!slist2.empty(), "Error in SList<T>::SList(const T (&arr)[]) or SList<T>::empty method");

	// Test copy-constructors
	List<int> list3(list2);
	dynamic_assert(list3.size() == list2.size(), "Error in List::List(const List<T>& other)");
	SList<int> slist3(slist2);
	dynamic_assert(slist3.size() == slist2.size(), "Error in SList::SList(const List<T>& other)");
}

/**
 * Tests the push_back/push_front/pop_back/pop_front methods of List and SList.
 */
static void TestPushAndPopMethods()
{
	List<int> list1;
	SList<int> slist1;

	// Test push_back method for empty lists
	list1.push_back(1);
	dynamic_assert(1 == list1.size(), "Error in List<T>::push_back for an empty list");

	slist1.push_back(1);
	dynamic_assert(1 == list1.size(), "Error in SList<T>::push_back for an empty list");

	// Test push_back method for already filled lists
	list1.push_back(2);
	dynamic_assert(2 == list1.size(), "Error in List<T>::push_back for an already filled list");
	list1.push_back(3);
	dynamic_assert(3 == list1.size(), "Error in List<T>::push_back for an already filled list");

	slist1.push_back(2);
	dynamic_assert(2 == slist1.size(), "Error in SList<T>::push_back for an already filled list");
	slist1.push_back(3);
	dynamic_assert(3 == slist1.size(), "Error in SList<T>::push_back for an already filled list");

	List<int> list2;
	SList<int> slist2;

	// Test push_front method for empty lists
	list2.push_front(1);
	dynamic_assert(1 == list2.size(), "Error in List<T>::push_front for an empty list");

	slist2.push_front(1);
	dynamic_assert(1 == slist2.size(), "Error in SList<T>::push_front for an empty list");

	// Test push_front method for already filled lists
	list2.push_front(2);
	dynamic_assert(2 == list2.size(), "Error in List<T>::push_front for an already filled list");
	list2.push_front(3);
	dynamic_assert(3 == list2.size(), "Error in List<T>::push_front for an already filled list");

	slist2.push_front(2);
	dynamic_assert(2 == slist2.size(), "Error in SList<T>::push_front for an already filled list");
	slist2.push_front(3);
	dynamic_assert(3 == slist2.size(), "Error in SList<T>::push_front for an already filled list");

	// Test pop_front method
	int front1 = list1.pop_front();
	dynamic_assert(1 == front1 && 2 == list1.size(), "Error in List<T>::pop_front or List<T>::push_back methods");
	int front2 = list2.pop_front();
	dynamic_assert(3 == front2 && 2 == list1.size(), "Error in List<T>::pop_front or List<T>::push_front methods");

	int sfront1 = slist1.pop_front();
	dynamic_assert(1 == sfront1 && 2 == slist1.size(), "Error in SList<T>::pop_front or SList<T>::push_back methods");
	int sfront2 = slist2.pop_front();
	dynamic_assert(3 == sfront2 && 2 == slist1.size(), "Error in SList<T>::pop_front or SList<T>::push_front methods");

	int front3 = list1.pop_front();
	dynamic_assert(2 == front3 && 1 == list1.size(), "Error in List<T>::pop_front or List<T>::push_back methods");
	int front4 = list2.pop_front();
	dynamic_assert(2 == front4 && 1 == list2.size(), "Error in List<T>::pop_front or List<T>::push_front methods");

	int sfront3 = slist1.pop_front();
	dynamic_assert(2 == sfront3 && 1 == slist1.size(), "Error in SList<T>::pop_front or SList<T>::push_back methods");
	int sfront4 = slist2.pop_front();
	dynamic_assert(2 == sfront4 && 1 == slist2.size(), "Error in SList<T>::pop_front or SList<T>::push_front methods");

	// Test if list is empty after removing all elements using pop_front
	list1.pop_front();
	dynamic_assert(0 == list1.size() && list1.empty(), "Error in List<T>::pop_front, the list is not empty after removing all elements");
	list2.pop_front();
	dynamic_assert(0 == list2.size() && list2.empty(), "Error in List<T>::pop_front, the list is not empty after removing all elements");
	slist1.pop_front();
	dynamic_assert(0 == slist1.size() && slist1.empty(), "Error in SList<T>::pop_front, the list is not empty after removing all elements");
	slist2.pop_front();
	dynamic_assert(0 == slist2.size() && slist2.empty(), "Error in SList<T>::pop_front, the list is not empty after removing all elements");

	// Fill two lists in order to test pop_back
	List<int> list3;
	SList<int> slist3;

	list3.push_back(2);
	dynamic_assert(1 == list3.size(), "Error in List<T>::push_back for an empty list");
	slist3.push_back(2);
	dynamic_assert(1 == slist3.size(), "Error in SList<T>::push_back for an empty list");

	list3.push_back(3);
	dynamic_assert(2 == list3.size(), "Error in List<T>::push_back for an already filled list");
	slist3.push_back(3);
	dynamic_assert(2 == slist3.size(), "Error in SList<T>::push_back for an already filled list");

	list3.push_front(1);
	dynamic_assert(3 == list3.size(), "Error in List<T>::push_front for an already filled list");
	slist3.push_front(1);
	dynamic_assert(3 == slist3.size(), "Error in SList<T>::push_front for an already filled list");

	// Test pop_back
	int back1 = list3.pop_back();
	dynamic_assert(3 == back1 && 2 == list3.size(), "Error in List<T>::pop_back or List<T>::push_front methods");
	int sback1 = slist3.pop_back();
	dynamic_assert(3 == sback1 && 2 == slist3.size(), "Error in SList<T>::pop_back or SList<T>::push_front methods");

	int back2 = list3.pop_back();
	dynamic_assert(2 == back2 && 1 == list3.size(), "Error in List<T>::pop_back or List<T>::push_back methods");
	int sback2 = slist3.pop_back();
	dynamic_assert(2 == sback2 && 1 == slist3.size(), "Error in SList<T>::pop_back or SList<T>::push_back methods");

	int back3 = list3.pop_back();
	dynamic_assert(1 == back3 && 0 == list3.size(), "Error in List<T>::pop_back or List<T>::push_back methods");
	int sback3 = slist3.pop_back();
	dynamic_assert(1 == sback3 && 0 == slist3.size(), "Error in SList<T>::pop_back or SList<T>::push_back methods");

	// Check if lists are empty after removing all elements using pop_back
	dynamic_assert(list3.empty(), "Error in List<T>::pop_back, the list is not empty after removing all elements");
	dynamic_assert(slist3.empty(), "Error in SList<T>::pop_back, the list is not empty after removing all elements");
}

/**
 * Tests the remove method of List and SList.
 */
static void TestRemoveMethod()
{
	const int elements[] = { 0,1,2,0,0,0,6,7,8,0 };

	// Prepare lists
	List<int> list(elements);
	SList<int> slist(elements);

	// Test remove
	list.remove(0);
	dynamic_assert(5 == list.size(), "Error in List<T>::remove");
	slist.remove(0);
	dynamic_assert(5 == slist.size(), "Error in SList<T>::remove");
}

/**
 * Tests the iterate method of List and SList which takes a function pointer as parameter.
 */
static void TestFirstIterateMethod()
{
	const int elements[] = { 0,1,2,3,4,5,6,7,8,9 };

	// Prepare lists
	List<int> list(elements);
	SList<int> slist(elements);

	// Prepare parameters
	struct IterationParams
	{
		int			m_index;
		const int*	m_elements;
	} params, sparams;
	params.m_index		= 0;
	params.m_elements	= elements;
	sparams.m_index		= 0;
	sparams.m_elements	= elements;

	// Prepare iteration functions
	auto iterateFunc = [](int& element, void* parameter) -> ListIterationAction
	{
		IterationParams* params = static_cast<IterationParams*>(parameter);
		if (element == params->m_elements[params->m_index])
		{
			params->m_index++;
			return ListIterationAction::ACTION_CONTINUE;
		}
		return ListIterationAction::ACTION_BREAK;
	};

	List<int>::IterationFunction func = iterateFunc;
	SList<int>::IterationFunction sfunc = iterateFunc;

	// Iterate the lists
	list.iterate(func, &params);
	slist.iterate(sfunc, &sparams);

	// Check the results of the iterations
	dynamic_assert(params.m_index == sizeof(elements) / sizeof(int), "Error in List<T>iterate(const typename List<T>::IterationFunction& func, void* parameter)");
	dynamic_assert(sparams.m_index == sizeof(elements) / sizeof(int), "Error in SList<T>iterate(const typename List<T>::IterationFunction& func, void* parameter)");

	// TODO: Test iterate methods using ListIterationAction::ACTION_BREAK and ListIterationAction::ACTION_REMOVE
}

/**
 * Tests the iterate method of List and SList which takes a lambda function as parameter.
 */
static void TestSecondIterateMethod()
{
	const int elements[] = { 0,1,2,3,4,5,6,7,8,9 };

	// Prepare lists
	List<int> list(elements);
	SList<int> slist(elements);

	int index;
	auto iterateFunc = [&](int& element) -> ListIterationAction
	{
		if (element == elements[index])
		{
			index++;
			return ListIterationAction::ACTION_CONTINUE;
		}
		return ListIterationAction::ACTION_BREAK;
	};

	// Iterate the first list
	index = 0;
	list.iterate(iterateFunc);
	dynamic_assert(index == sizeof(elements) / sizeof(int), "Error in List<T>::iterate(const Lambda& func)");

	// Iterate the second list
	index = 0;
	slist.iterate(iterateFunc);
	dynamic_assert(index == sizeof(elements) / sizeof(int), "Error in SList<T>::iterate(const Lambda& func)");

	// TODO: Test iterate methods using ListIterationAction::ACTION_BREAK and ListIterationAction::ACTION_REMOVE
}

/**
 * Tests the operator methods of List and SList.
 */
static void TestOperators()
{
	const int elements1[] = { 0,1,2,3,4,5,6,7,8,9 };
	const int elements2[] = { 0,1,2,3,4,5,6,7,8,0 };
	const int elements3[] = { 0,1,2,3,4,5,6,7,8,9,10 };

	// Prepare lists
	List<int> list1(elements1);
	List<int> list2;
	List<int> list3(elements2);
	List<int> list4(elements3);
	SList<int> slist1(elements1);
	SList<int> slist2;
	SList<int> slist3(elements2);
	SList<int> slist4(elements3);

	// Test operator=
	list2 = list1;
	slist2 = slist1;

	// Test operator==
	dynamic_assert(list1 == list2, "Error in List<T>::operator== or List<T>::operator=");
	dynamic_assert(slist1 == slist2, "Error in SList<T>::operator== or SList<T>::operator=");
	dynamic_assert(!(list1 == list4), "Error in List<T>::operator==");
	dynamic_assert(!(slist1 == slist4), "Error in SList<T>::operator==");

	// Test operator!=
	dynamic_assert(list1 != list3, "Error in List<T>::operator!=");
	dynamic_assert(slist1 != slist3, "Error in SList<T>::operator!=");
	dynamic_assert(list1 != list4, "Error in List<T>::operator!=");
	dynamic_assert(slist1 != slist4, "Error in SList<T>::operator!=");
}

/**
 * Tests the thread-safety of SList.
 */
static void TestThreadSafety()
{
	int result[300];
	std::thread threads[300];
	SList<int> slist;
	
	// Fill the result array with zeros
	for(int i = 0; i < 300; i++)
	{
		result[i] = 0;
	}

	auto pushBackThread = [&](int element) -> void
	{
		slist.push_back(element);
	};

	auto pushFrontThread = [&](int element) -> void
	{
		slist.push_front(element);
	};
	
	// Fill slist with numbers from 0 to 149 using threads calling push_back
	for(int i = 0; i < 150; i++)
	{
		threads[i] = std::thread(pushBackThread, i);
	}
	
	// Fill slist with numbers from 150 to 299 using threads calling push_front
	for(int i = 150; i < 300; i++)
	{
		threads[i] = std::thread(pushFrontThread, i);
	}
	
	// Wait for all threads to finish
	for(int i = 0; i < 300; i++)
	{
		threads[i].join();
	}
	
	// Fill the result array with values from slist
	int index = 0;
	auto listToArray = [&](int& element) -> ListIterationAction
	{
		result[index++] = element;
		return ListIterationAction::ACTION_CONTINUE;
	};
	slist.iterate(listToArray);
	
	// Check the values of the result array
	for(int i = 0; i < 300; i++)
	{
		bool foundOnce = false;
		for(int j = 0; j < 300; j++)
		{
			dynamic_assert(result[j] >= 0 && result[j] < 300, "Error testing the thread-safety, result arrray contains an unexpected value");
			if(i == result[j])
			{
				dynamic_assert(!foundOnce, "Error testing the thread-safety, result array contains a value more than once");
				foundOnce = true;
			}
		}
	}
}

/**
 * Main function of the program. Runs all tests.
 */
int main(int argc, char* argv[])
{
	TestConstructors();
	TestPushAndPopMethods();
	TestRemoveMethod();
	TestFirstIterateMethod();
	TestSecondIterateMethod();
	TestOperators();
	TestThreadSafety();
	
	std::cout << "All tests done!" << std::endl;
	return 0;
}
