#include <iostream>
#include "iterator.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		std::allocator<T> allo;
		typedef T		value_type;
		typedef Alloc	allocator_type;
		typedef size_t	size_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
	public:
		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0) , _begin(NULL), _end(NULL), _end_of_storage(NULL){}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_begin = alloc.allocate(n);
			_end = _begin + n;
			_end_of_storage = _end
			for (size_type i = 0; i < n; ++i)
				alloc.construct(_begin + i, val);
			_size = n;
		}
		vector (const vector& x)
		{
			_begin = alloc.allocate(x._size);
			_size = x._size;
			_end = _begin + _size;
			_end_of_storage = _end;
			for (size_type i = 0; i < _size; ++i)
				alloc.construct(_begin + i, x._begin[i]);
		}
		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		{
			_size = last - first;
			_begin = alloc.allocate(_size);
			_end = _begin + _size;
			_end_of_storage = _end;
			for (InputIterator	it = first; it != last; ++it)
				alloc.construct(_begin + (it - first), *it);
		}
		~vector()
		{
			for (size_type i = 0; i < _size; ++i)
				alloc.destroy(_begin + i);
			alloc.deallocate(_begin, _size);
		}
		vector& operator= (const vector& x)
		{
			if (this != &x)
			{

			}
			return *this;
		}
	private:
		size_type _size;
		pointer _begin;
		pointer _end;
		pointer _end_of_storage;
	};
}
