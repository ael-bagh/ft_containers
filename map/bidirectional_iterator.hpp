#pragma once
#include "RB_tree.hpp"
namespace ft
{
    template<class T>   
    struct node;

    template<class T> 
    node<T> *successor(const node<T> *nd);
    template<class T> 
    node<T> *predecessor(const node<T> *nd);

    template <class T>
    struct const_bidirectional_iterator;

    template <class T>
    struct bidirectional_iterator
    {
            typedef node<T> node_type;
            typedef T value_type;
            typedef node_type* pointer;
            typedef std::ptrdiff_t difference_type;
            bidirectional_iterator(): _ptr(NULL) {}
            bidirectional_iterator(pointer ptr): _ptr(ptr) {}
            bidirectional_iterator(const bidirectional_iterator& x): _ptr(x._ptr) {}
            bidirectional_iterator(const const_bidirectional_iterator<T>& x): _ptr(x.base()) {}
            pointer base() const
            {
                return _ptr;
            }
            bidirectional_iterator& operator= (const bidirectional_iterator& x)
            {
                _ptr = x._ptr;
                return *this;
            }
            bidirectional_iterator& operator++ ()
            {
                _ptr = successor(_ptr);
                return *this;
            }
            bidirectional_iterator operator++ (int)
            {
                bidirectional_iterator tmp = *this;
                _ptr = successor(_ptr);
                return tmp;
            }
            bidirectional_iterator& operator-- ()
            {
                _ptr = predecessor(_ptr);
                return *this;
            }
            bidirectional_iterator operator-- (int)
            {
                bidirectional_iterator tmp = *this;
                _ptr = predecessor(_ptr);
                return tmp;
            }
            bool operator== (const bidirectional_iterator& x) const
            {
                return _ptr == x._ptr;
            }
            bool operator!= (const bidirectional_iterator& x) const
            {
                return !(_ptr == x._ptr);
            }
            T operator*()
            {
                return _ptr->value;
            }
            T* operator->()
            {
                return &(_ptr->value);
            }
        private:
            pointer _ptr;
    };

    template <class T>
    struct const_bidirectional_iterator
    {
            typedef node<T> node_type;
            typedef T value_type;
            typedef const node_type* pointer;
            typedef std::ptrdiff_t difference_type;
            const_bidirectional_iterator(): _ptr(NULL) {}
            const_bidirectional_iterator(pointer ptr): _ptr(ptr) {}
            const_bidirectional_iterator(const const_bidirectional_iterator& x): _ptr(x._ptr) {}
            const_bidirectional_iterator(const bidirectional_iterator<T>& x): _ptr(x.base()) {}
            pointer base() const
            {
                return _ptr;
            }
            const_bidirectional_iterator& operator= (const const_bidirectional_iterator& x)
            {
                _ptr = x._ptr;
                return *this;
            }
            const_bidirectional_iterator& operator++ ()
            {
                _ptr = successor(_ptr);
                return *this;
            }
            const_bidirectional_iterator operator++ (int)
            {
                const_bidirectional_iterator tmp = *this;
                _ptr = successor(_ptr);
                return tmp;
            }
            const_bidirectional_iterator& operator-- ()
            {
                _ptr = predecessor(_ptr);
                return *this;
            }
            const_bidirectional_iterator operator-- (int)
            {
                const_bidirectional_iterator tmp = *this;
                _ptr = predecessor(_ptr);
                return tmp;
            }
            bool operator== (const const_bidirectional_iterator& x) const
            {
                return _ptr == x._ptr;
            }
            bool operator!= (const const_bidirectional_iterator& x) const
            {
                return !(_ptr == x._ptr);
            }
            const T operator*() const
            {
                return _ptr->value;
            }
            const T *operator->() const
            {
                return &(_ptr->value);
            }
        private:
            pointer _ptr;
    };
}

