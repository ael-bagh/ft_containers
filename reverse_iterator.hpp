#pragma once 
#include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    struct reverse_iterator 
    {
        typedef T  iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
        //constructors/////
        reverse_iterator(): _it(NULL) {};
        explicit reverse_iterator(iterator_type x): _it(x) {}
        template <class U>
        reverse_iterator(const reverse_iterator<U> &u)
        {
            _it = u.base();
        }
        //conversion/////
        iterator_type base() const
        {
            return _it;
        }
        //operators/////
        reference operator*() const
        {
            iterator_type tmp = _it;
            return *--tmp;
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        reverse_iterator& operator++()
        {
            --_it;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            --_it;
            return tmp;
        }
        reverse_iterator& operator--()
        {
            ++_it;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            ++_it;
            return tmp;
        }
        reverse_iterator& operator+=(difference_type n)
        {
            _it -= n;
            return *this;
        }
        reverse_iterator& operator-=(difference_type n)
        {
            _it += n;
            return *this;
        }
        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(_it - n);
        }
        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(_it + n);
        }
        reference operator[](difference_type n) const
        {
            return _it[-n-1];
        }
        private:
            iterator_type _it;
    };
    template <class Iterator, class Iterator2>
    bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return x.base() == y.base();
    }
    template <class Iterator, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return x.base() != y.base();
    }
    template <class Iterator, class Iterator2>
    bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return x.base() > y.base();
    }
    template <class Iterator, class Iterator2>
    bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return x.base() < y.base();
    }
    template <class Iterator, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return x.base() >= y.base();
    }
    template <class Iterator, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return x.base() <= y.base();
    }
    template <class Iterator, class Iterator2>
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator2>& y)
    {
        return y.base() - x.base();
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x)
    {
        return reverse_iterator<Iterator>(x.base() - n);
    }
}