#ifdef _STACK_

template <typename T>
stack<T>::stack()
{
    element_ = NULL;
    setSize_(0);
}

template <typename T>
stack<T>::stack(stack<T>& other)
{
    element_ = NULL;
    setSize_(other.getSize());
}

template <typename T>
stack<T>::~stack() {free(element_);}

template <typename T>
void stack<T>::setSize_(size_t size)
{
    if (size == 0) size_ = 0;
    else
    {
        if (!(element_ = (T*) realloc(element_, size_)))
        {
            std::cout << "reallocation failure" << std::endl;
            exit(0);
        }
        size_ = size;
    }
}

template <typename T>
size_t stack<T>::getSize(){return size_;}

template <typename T>
void stack<T>::push(T element)
{
    setSize_(size_ + 1);
    element_[size_ - 1] = element;
}

template <typename T>
T stack<T>::pop()
{
    if (size_  <= 0)
    {
        std::cerr << "can`t pop, size_ = 0" << std::endl;
        exit(0);
    }
    T tmp = element_[size_ - 1];
    setSize_(size_ - 1);
    return tmp;
}

template <typename T>
T stack<T>::back() {return element_[size_ - 1];}

template <typename T>
void stack<T>::clear() {setSize_(0);}

template <typename T>
bool stack<T>::isEmpty()
{
    if (size_ == 0) return true;
    else return false;
}
#endif
