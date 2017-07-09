#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

#include <iostream>

template <class T>
class MySharedPtr
{
public:
    MySharedPtr();
    MySharedPtr(T* ptr);
    MySharedPtr(const MySharedPtr<T>& p_num);//const?
    virtual ~MySharedPtr();
    T* get() const;
    T& operator*();
    T* operator->();
    void operator=(const MySharedPtr<T>& p_num);
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
MySharedPtr<T>::MySharedPtr(T *ptr)
{
    counter_ = new int;
    *counter_= 1;
    pointer_ = ptr;
}


template <class T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr& p_num)//const?
{
    counter_ = p_num.counter_;
    (*counter_)++;
    pointer_ = p_num.pointer_;
}

template<class T>
MySharedPtr<T>::~MySharedPtr()
{
    (*counter_)--;
    if (*counter_ == 0)
    {
        delete pointer_; //omer
        delete counter_;
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
            delete counter_;
            delete pointer_;
        }
        counter_ = ptr.counter_;
        (*counter_)++;
        pointer_ = ptr.pointer_;
    }
}


#endif // _MY_SHARED_PTR_H_
