#include "iterator_traits.hpp"

namespace ft 
{
    template <class T>
    struct iterator
    {
        typedef ft::iterator_base<std::random_access_iterator_tag, T>  iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
        iterator(): _ptr(NULL) {}
        iterator(pointer ptr): _ptr(ptr) {}
        iterator(const iterator& x): _ptr(x._ptr) {}
        pointer base() const
        {
            return _ptr;
        }
        iterator& operator= (const iterator& x)
        {
            _ptr = x._ptr;
            return *this;
        }
        operator iterator<const T>() const
		{
			return(iterator<const T>(_ptr));
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
    
    template <class YT>
    iterator<YT> operator+(typename iterator<YT>::difference_type n, const iterator<YT>& x)
    {
        return iterator<YT>(x.base() + n);
    }

    template <class YT>
    iterator<YT> operator-(typename iterator<YT>::difference_type n, const iterator<YT>& x)
    {
        return iterator<YT>(x.base() - n);
    }

    template <class YT, class XT>
    typename iterator<YT>::difference_type operator-(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() - x.base());
    }
    template <class YT, class XT>
    bool operator!=(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() != x.base());
    }
    template <class YT, class XT>
    bool operator==(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() == x.base());
    }
    template <class YT, class XT>
    bool operator<=(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() <= x.base());
    }
    template <class YT, class XT>
    bool operator>=(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() >= x.base());
    }
    template <class YT, class XT>
    bool operator<(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() < x.base());
    }
    template <class YT, class XT>
    bool operator>(const iterator<YT>& y, const iterator<XT>& x)
    {
        return (y.base() > x.base());
    }
}