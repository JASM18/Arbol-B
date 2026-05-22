template <typename T>
ArbolB<T>::ArbolB()
{
    //ctor
}

template <typename T>
ArbolB<T>::~ArbolB()
{
    //dtor
}

template <typename T>
ArbolB<T>::ArbolB(const ArbolB& other)
{
    //copy ctor
}

template <typename T>
ArbolB<T>& ArbolB<T>::operator=(const ArbolB<T>& arbol)
{
    if (this == &arbol) return *this; // handle self assignment
    //assignment operator

    // codigo...

    return *this;
}
