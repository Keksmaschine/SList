# SList
An implementation of a thread-safe list which provides methods similar to the class std::list of the STL.

There are two use cases where thread-safety of the class SList is not guaranteed:
1) If you explicitly call methods of the base class List (this is the obvious case)
2) If you upcast an instance of SList to a List reference/pointer and call the iterate(const Lambda& func) method for this reference/pointer

Some methods of the class List are not declared as const although they do not change the state of the object. The reason for this is that the equivalent methods in SList do change the state of the object. Declaring these methods as const in the base class List would change the signature of these methods and we would not be able to override them in the derived class SList.
