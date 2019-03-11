#ifdef _MYVECTOR_

#include "MyVector.h"
#include <iostream>

using namespace std;

template <typename T> 
MyVector<T>::MyVector()
{
	element_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template <typename T>
MyVector<T>::~MyVector()
{
	element_ = nullptr;
	size_ = 0;
}



template <typename T>
MyVector<T>::MyVector(const MyVector<T>& that)
{
	int tmp = that.capacity();
	element_ = new T[tmp];
	capacity_ = that.capacity();
	size_ = that.size();
	for (int i = 0; i < size_; i++)
		element_[i] = that[i];
}
template<typename T>
T& MyVector<T>::operator [] (const int i) const
{
	if ((i >= size_) || (i < 0))
		cout << "operator[]: outbound container" << endl;
	return element_[i];
}
template<typename T>
void MyVector<T>::swap_(MyVector<T>& that) noexcept
{
	MyVector tmp(*this);
	//= нельзя писать потому то такого оператора мы не знаем
	element_ = new T[that.capacity()];
	size_ = that.size();
	capacity_ = that.capacity();
	for (int i = 0; i < size_; i++)
		element_[i] = that[i];
	that.reserve(tmp.capacity());
	for (int i = 0; i < tmp.size(); i++)
		that.push_back(tmp[i]);
}

//Выделяет память размером newCapacity, Если newCapacity < size_, то size_ = capacity_ = newCapacity_; 
template<typename T>
void MyVector<T>::reserve(int newCapacity)
{
	if (newCapacity >= 0)
	{
		MyVector tmp(*this);
		delete[] element_;
		element_ = new T[newCapacity];
		if (newCapacity > size_)
			for (int i = 0; i < size_; i++)
				element_[i] = tmp[i];
		else
		{
			for (int i = 0; i < newCapacity; i++)
				element_[i] = tmp[i];
			size_ = newCapacity;
		}
		capacity_ = newCapacity;
	}
}
template<typename T>
const MyVector<T>& MyVector<T>::operator=(const MyVector<T>& that)
{
	if (this != &that)
		MyVector(that).swap_(*this);
	return *this;
}
//Если newSize > capacity то вызывает reserve(newsize*k), если newSize < capacity, то 
//Если newSize > size_ , то дописывает нули, если нет, то уменьшает size_  до  newSize и обновляет capacity_
template<typename T>
void MyVector<T>::resize(const int& newSize)
{
	if (newSize <= 0)
	{
		reserve(0);
		size_ = 0;
	}
	if (newSize > capacity_)
	{
		reserve(newSize * 1.5);
		for (int i = size_; i < newSize; i++)
			element_[i] = 0;
	}
	else 
		if (newSize > size_)
			for (int i = size_; i < newSize; i++)
				element_[i] = 0;
	size_ = newSize;
}

template <typename T> 
void MyVector<T>::push_back(const T &value)
{
	resize(size_ + 1);
	element_[size_ - 1] = value;
}
template <typename T>
void MyVector<T>::pop_back()
{
	if ((int)(size_* k * k) < capacity_)
		reserve((int)(capacity_ / k));
	resize(size_ - 1);
}
#endif

