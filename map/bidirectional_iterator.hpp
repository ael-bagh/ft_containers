#pragma once
#include "RB_tree.hpp"
#include "../iterator_traits.hpp"
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
            typedef typename std::bidirectional_iterator_tag iterator_category;
            typedef node<T> node_type;
            typedef T value_type;
            typedef node_type* pointer;
            typedef T& reference;
            typedef T* ppointer;
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
            reference operator*() const
            {
                return _ptr->value;
            }
            ppointer operator->() const
            {
                return &(operator*());
            }
        private:
            pointer _ptr;
    };

    template <class T>
    struct const_bidirectional_iterator
    {
            typedef typename std::bidirectional_iterator_tag iterator_category;
            typedef node<T> node_type;
            typedef const T value_type;
            typedef const node_type* pointer;
            typedef const T& reference;
            typedef const T* ppointer;
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
            reference operator*() const
            {
                return _ptr->value;
            }
            ppointer operator->() const
            {
                return &(operator*());
            }
        private:
            pointer _ptr;
    };

    template <class TL, class TR>
    bool operator== (const bidirectional_iterator<TL>& x, const bidirectional_iterator<TR>& y)
    {
        return x.base() == y.base();
    }
    template <class TL, class TR>
    bool operator!= (const bidirectional_iterator<TL>& x, const bidirectional_iterator<TR>& y)
    {
        return x.base() != y.base();
    }
}

