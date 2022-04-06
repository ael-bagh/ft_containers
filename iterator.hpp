#include "iterator_traits.hpp"

namespace ft 
{
    template <class T>
    struct vector_iterator
    {
        typedef typename iterator_traits<T*>::pointer pointer;
        typedef typename iterator_traits<pointer>::reference reference;
        typedef typename iterator_traits<pointer>::value_type value_type;
        typedef typename iterator_traits<pointer>::difference_type difference_type;
        typedef typename iterator_traits<pointer>::iterator_category iterator_category;
        vector_iterator(): _ptr(NULL) {}
        vector_iterator(pointer ptr): _ptr(ptr) {}
        vector_iterator(const vector_iterator& x): _ptr(x._ptr) {}
        vector_iterator& operator= (const vector_iterator& x)
        {
            _ptr = x._ptr;
            return *this;
        }
        vector_iterator& operator++ ()
        {
            ++_ptr;
            return *this;
        }
        vector_iterator operator++ (int)
        {
            vector_iterator tmp = *this;
            ++_ptr;
            return tmp;
        }
        vector_iterator& operator-- ()
        {
            --_ptr;
            return *this;
        }
        vector_iterator operator-- (int)
        {
            vector_iterator tmp = *this;
            --_ptr;
            return tmp;
        }
        vector_iterator& operator+= (difference_type n)
        {
            _ptr += n;
            return *this;
        }
        vector_iterator& operator-= (difference_type n)
        {
            _ptr -= n;
            return *this;
        }
        vector_iterator operator+ (difference_type n) const
        {
            return vector_iterator(_ptr + n);
        }
        vector_iterator operator- (difference_type n) const
        {
            return vector_iterator(_ptr - n);
        }
        difference_type operator- (const vector_iterator& x) const
        {
            return _ptr - x._ptr;
        }
        reference operator[] (difference_type n) const
        {
            return _ptr[n];
        }
        reference operator* () const
        {
            return *_ptr;
        }
        pointer operator-> () const
        {
            return _ptr;
        }
        bool operator== (const vector_iterator& x) const
        {
            return _ptr == x._ptr;
        }
        bool operator!= (const vector_iterator& x) const
        {
            return _ptr != x._ptr;
        }
        bool operator< (const vector_iterator& x) const
        {
            return _ptr < x._ptr;
        }
        bool operator> (const vector_iterator& x) const
        {
            return _ptr > x._ptr;
        }
        bool operator<= (const vector_iterator& x) const
        {
            return _ptr <= x._ptr;
        }
        bool operator>= (const vector_iterator& x) const
        {
            return _ptr >= x._ptr;
        }
        private:
            pointer _ptr;
    };
}