#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_
#include <iostream>

template <class T> 
class MySharedPtr 
{
public:
	MySharedPtr(T* type);
	MySharedPtr(MySharedPtr& ptr);//const?
	virtual ~MySharedPtr();
	T* get();
	T& operator*();
	/*T* opertaor->();*/
	//MySharedPtr<T>& opertaor = (const MySharedPtr<T>& ptr);
private:
	int* counter_;
	T* pointer_;
};
//
//template <class T>
//MySharedPtr<T>::MySharedPtr(T* type)
//{
//	new int *counter_ = 1;
//	pointer_ = type;
//}
//
//
//template <class T>
//MySharedPtr<T>::MySharedPtr(MySharedPtr& ptr)//const?
//{
//	counter_ = ptr.pointer;
//	*counter_++;
//	pointer_ = ptr.pointer;
//}
//
//template<class T>
//MySharedPtr<T>::~MySharedPtr()
//{
//	*counter--;
//	if (*counter_ == 0)
//	{
//		free(pointer_);
//		free(counter_);
//	}
//}
//
//template <class T>
//T* MySharedPtr<T> ::get()
//{
//	return pointer_;
//}
//
//template <class T>
//T& MySharedPtr<T>::operator*()
//{
//	return *pointer_;
//}
//
//template <class T>
//T* MySharedPtr<T>::operator->()
//{
//	return pointer_;
//}
//
//template <class T>
//MySharedPtr& MySharedPtr<T>::operator=(const MySharedPtr& ptr) 
//{
//	if (this == &ptr)
//		return *this;
//	(*counter_)--;
//	delete this;
//	MySharedPtr p = new MySharedPtr(ptr);
//	//return *p;
//	return this;
//}


#endif // _MY_SHARED_PTR_H_




