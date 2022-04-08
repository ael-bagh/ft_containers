#include "iterator_traits.hpp"

namespace ft 
{
    template <class T>
    struct iterator
    {
        typedef typename iterator_traits<T*>::pointer pointer;
        typedef typename iterator_traits<pointer>::reference reference;
        typedef typename iterator_traits<pointer>::value_type value_type;
        typedef typename iterator_traits<pointer>::difference_type difference_type;
        typedef typename iterator_traits<pointer>::iterator_category iterator_category;
        iterator(): _ptr(NULL) {}
        iterator(pointer ptr): _ptr(ptr) {}
        iterator(const iterator& x): _ptr(x._ptr) {}
        iterator& operator= (const iterator& x)
        {
            _ptr = x._ptr;
            return *this;
        }
        iterator& operator++ ()
        {
            ++_ptr;
            return *this;
        }
        iterator operator++ (int)
        {
            iterator tmp = *this;
            ++_ptr;
            return tmp;
        }
        iterator& operator-- ()
        {
            --_ptr;
            return *this;
        }
        iterator operator-- (int)
        {
            iterator tmp = *this;
            --_ptr;
            return tmp;
        }
        iterator& operator+= (difference_type n)
        {
            _ptr += n;
            return *this;
        }
        iterator& operator-= (difference_type n)
        {
            _ptr -= n;
            return *this;
        }
        iterator operator+ (difference_type n) const
        {
            return iterator(_ptr + n);
        }
        iterator operator- (difference_type n) const
        {
            return iterator(_ptr - n);
        }
        difference_type operator- (const iterator& x) const
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
        bool operator== (const iterator& x) const
        {
            return _ptr == x._ptr;
        }
        bool operator!= (const iterator& x) const
        {
            return _ptr != x._ptr;
        }
        bool operator< (const iterator& x) const
        {
            return _ptr < x._ptr;
        }
        bool operator> (const iterator& x) const
        {
            return _ptr > x._ptr;
        }
        bool operator<= (const iterator& x) const
        {
            return _ptr <= x._ptr;
        }
        bool operator>= (const iterator& x) const
        {
            return _ptr >= x._ptr;
        }
        private:
            pointer _ptr;
    };
    template <class Iterator>
    struct reverse_iterator
    {
        typedef iterator<Iterator> iterator_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

        reverse_iterator(): _it(NULL) {}
        explicit reverse_iterator(iterator_type it): _it(it) {}
        template<class Iter>
        reverse_iterator(const reverse_iterator<Iter>& x): _it(x._it) {}
        reverse_iterator& operator= (const reverse_iterator& x)
        {
            _it = x._it;
            return *this;
        }
        reverse_iterator& operator++ ()
        {
            --_it;
            return *this;
        }
        reverse_iterator operator++ (int)
        {
            reverse_iterator tmp = *this;
            --_it;
            return tmp;
        }
        reverse_iterator& operator-- ()
        {
            ++_it;
            return *this;
        }
        reverse_iterator operator-- (int)
        {
            reverse_iterator tmp = *this;
            ++_it;
            return tmp;
        }
        reverse_iterator& operator+= (difference_type n)
        {
            _it -= n;
            return *this;
        }
        reverse_iterator& operator-= (difference_type n)
        {
            _it += n;
            return *this;
        }
        reverse_iterator operator+ (difference_type n) const
        {
            return reverse_iterator(_it - n);
        }
        reverse_iterator operator- (difference_type n) const
        {
            return reverse_iterator(_it + n);
        }
        difference_type operator- (const reverse_iterator& x) const
        {
            return x._it - _it;
        }
        reference operator[] (difference_type n) const
        {
            return _it[-n];
        }
        reference operator* () const
        {
            return *_it;
        }
        pointer operator-> () const
        {
            return _it;
        }
        bool operator== (const reverse_iterator& x) const
        {
            return _it == x._it;
        }
        bool operator!= (const reverse_iterator& x) const
        {
            return _it != x._it;
        }
        bool operator< (const reverse_iterator& x) const
        {
            return _it > x._it;
        }
        bool operator> (const reverse_iterator& x) const
        {
            return _it < x._it;
        }
        bool operator<= (const reverse_iterator& x) const
        {
            return _it >= x._it;
        }
        bool operator>= (const reverse_iterator& x) const
        {
            return _it <= x._it;
        }
        private:
            iterator_type _it;
    };
}