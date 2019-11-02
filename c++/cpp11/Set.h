#pragma once

/////////////////////////////////////////////////////////////////////////////
template<class T>
class Set
{
public:
    Set();
    Set(std::initializer_list<T> list);
    Set(const Set<T>& set);
    Set(Set<T>&& set);
    ~Set();

    void append(const T& item);
    void append(const Set<T>& set);

    Set<T>& operator =(const Set<T>& rhs);
    Set<T>& operator =(Set<T>&& rhs);

    template <typename U>
    friend Set<U> operator + (const Set<U>& lhs, const Set<U>& rhs);
private:
    vector<T> vec;
};

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>::Set()
{
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>::Set(std::initializer_list<T> list) : Set()
{
    for (auto i : list)
        append(i);
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>::Set(const Set<T>& set)
{
    *this = set;
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>::Set(Set<T>&& set)
{
    *this = std::move(set);
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>::~Set()
{
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>& Set<T>::operator =(const Set<T>& rhs)
{
    if (this != &rhs) {
        vec = rhs.vec;
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T>& Set<T>::operator =(Set<T>&& rhs)
{
    if (this != &rhs) {
        vec = std::move(rhs.vec);
    }

    return *this;
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
void Set<T>::append(const T& item)
{
    if (std::find(vec.begin(), vec.end(), item) == vec.end())
        vec.push_back(item);
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
void Set<T>::append(const Set<T>& set)
{
    for (auto i : set.vec)
        append(i);
}

/////////////////////////////////////////////////////////////////////////////
template<class T>
Set<T> operator + (const Set<T>& lhs, const Set<T>& rhs)
{
    Set<T> output;

    output.append(lhs);
    output.append(rhs);

    return output;
}
