#ifndef _MYVECTOR_
#define _MYVECTOR_
const float k = 1.5;
const int BUFFER = 1024;
template <typename T> class MyVector
{
private:
	T* element_;
	int size_;
	int capacity_;
	void swap_(MyVector<T>& toSwap) noexcept;
public:
	MyVector();
	MyVector(const MyVector<T>& that);
	~MyVector();
	void push_back(const T &value);
	void pop_back();
	inline int capacity() const { return capacity_; };
	void resize(const int& newSize);
	inline int size() const { return size_; };
	T& operator [] (const int i) const;
	void reserve(int newCap);
	const MyVector<T>& operator =(const MyVector<T>& that);
};
#include "MyVector.cpp"
#endif
