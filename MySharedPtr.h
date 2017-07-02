#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_
#include <iostream>

template <class T>
class MySharedPtr
{
public:
	MySharedPtr();
    MySharedPtr(T* type);
    MySharedPtr(MySharedPtr& ptr);//const?
    virtual ~MySharedPtr();
    T* get() const;
    T& operator*();
    T* operator->();
    void operator=(const MySharedPtr<T>& ptr);
	/*ostream& operator<<(ostream& ro);*/
    T* pointer_;
private:
    int* counter_;

};

template <class T>
MySharedPtr<T>::MySharedPtr()
{
	counter_ = new int;
	*counter_ = 0;
	pointer_ = NULL;
}

template <class T>
MySharedPtr<T>::MySharedPtr(T* type)
{
    counter_ = new int;
    *counter_= 1;
    pointer_ = type;
}


template <class T>
MySharedPtr<T>::MySharedPtr(MySharedPtr& ptr)//const?
{
    counter_ = ptr.counter_;
    (*counter_)++;
    pointer_ = ptr.pointer_;
}

template<class T>
MySharedPtr<T>::~MySharedPtr()
{
    (*counter_)--;
    if (*counter_ == 0)
    {
        free(pointer_);
        free(counter_);
    }
}

template <class T>
T* MySharedPtr<T> ::get() const
{
    return pointer_;
}

template <class T>
T& MySharedPtr<T>::operator*()
{
    return *pointer_;
}

template <class T>
T* MySharedPtr<T>::operator->()
{
    return pointer_;
}

template <class T>
void MySharedPtr<T>::operator=(const MySharedPtr<T>& ptr)
{
    if (this != &ptr)
    {
        (*counter_)--;
        if (counter_==0){
            free(counter_);
            free(pointer_);
        }
        counter_ = ptr.counter_;
        (*counter_)++;
        pointer_ = ptr.pointer_;
    }
}
//
//template<class T>
//ostream& MySharedPtr<T>::operator<<(ostream& ro)
//{
//	cout << *pointer_;
//}

#endif // _MY_SHARED_PTR_H_




