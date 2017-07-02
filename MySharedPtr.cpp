#include "MySharedPtr.h"

template <class T>
MySharedPtr<T>::MySharedPtr(T* type)
{
	new int *counter_ = 1;
	pointer_ = type;
}


template <class T>
MySharedPtr<T>::MySharedPtr(MySharedPtr& ptr)//const?
{
	counter_ = ptr.pointer;
	*counter_++;
	pointer_ = ptr.pointer;
}

template<class T>
MySharedPtr<T>::~MySharedPtr()
{
	*counter--;
	if (*counter_ == 0)
	{
		free(pointer_);
		free(counter_);
	}
}

template <class T>
T* MySharedPtr<T> :: get()
{
	return pointer_;
}

template <class T>
T& MySharedPtr<T>::operator*()
{
	return *pointer_;
}

//template <class T>
//T* MySharedPtr<T>::operator->()
//{
//	return pointer_;
//}

//template <class T>
//MySharedPtr<T>& MySharedPtr<T>::operator=(const MySharedPtr<T>& ptr) 
//{
//	if (this == &ptr)
//		return *this;
//	(*counter_)--;
//	delete this;
//	MySharedPtr p = new MySharedPtr(ptr);
//	return *p;
//}


