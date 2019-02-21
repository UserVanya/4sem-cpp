#ifndef _STACK_
#define _STACK_
#include <iostream>

template <typename T>
class stack {
public:
    stack();
    stack(stack& other);
    ~stack ();
    bool isEmpty();
    size_t getSize();
    void push(T element);
    T pop();
    T back();
    void clear();

private:
    T* element_;
    size_t size_;
    void setSize_ (size_t size);
};
#include "stack.cpp"
#endif
