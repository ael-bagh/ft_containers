#include <iostream>
#include "iterator.hpp"
#include "enable_if.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T		value_type;
		typedef Alloc	allocator_type;
		typedef size_t	size_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::iterator<pointer> iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::iterator<const_pointer> const_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		explicit vector (const allocator_type& alloc = allocator_type()) : _begin(NULL), _end(NULL), _end_of_storage(NULL), allo(alloc){}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : allo(alloc)
		{
			_begin = allo.allocate(n);
			_end = _begin + n;
			_end_of_storage = _end;
			for (size_type i = 0; i < n; ++i)
				allo.construct(_begin + i, val);
		}
		template <class InputIterator>
    	vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,const allocator_type& alloc = allocator_type()) : allo(alloc)
		{
			_begin = allo.allocate(last - first);
			_end = _begin + (last - first);
			_end_of_storage = _end;
			for (InputIterator it = first; it != last; ++it)
				allo.construct(_begin + (it - first), *it);
		}
		vector (const vector& x)
		{
			_begin = allo.allocate(x.size());
			_end = _begin + x.size();
			_end_of_storage = _end;
			for (size_type i = 0; i < size(); ++i)
				allo.construct(_begin + i, x._begin[i]);
		}
		~vector()
		{
			for (size_type i = 0; i < size(); ++i)
				allo.destroy(_begin + i);
			allo.deallocate(_begin, size());
			_begin = NULL;
			_end = NULL;
			_end_of_storage = NULL;
		}
		vector& operator= (const vector& x)
		{
			if (this != &x)
			{
				if (size())
				{
					for (size_type i = 0; i < size(); ++i)
						allo.destroy(_begin + i);
					allo.deallocate(_begin, capacity());
					_begin = allo.allocate(x.capacity());
					_end = _begin + x.size();
					_end_of_storage = _begin + x.capacity();
					for (size_type i = 0; i < x.size(); ++i)
						allo.construct(_begin + i, x._begin[i]);
				}
			}
			return *this;
		}
		//iterators
		iterator begin()
		{
			return iterator(_begin);
		}
		const_iterator begin() const
		{
			return const_iterator(_begin);
		}
		iterator end()
		{
			return iterator(_end);
		}
		const_iterator end() const
		{
			return const_iterator(_end);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}
		//capacity
		size_type size() const
		{
			return _end - _begin;
		}
		size_type max_size() const
		{
			return allo.max_size();
		}
		size_type capacity() const
		{
			return _end_of_storage - _begin;
		}
		void resize (size_type n, value_type val = value_type())
		{
			if (n < size())
			{
				for (size_type i = n; i < size(); ++i)
					allo.destroy(_begin + i);
				_end_of_storage = _begin + size() + 1;
			}
			else
			{
				if (n > capacity())
				{
					size_type new_capacity = n < capacity() * 2 ? capacity() * 2 : n;
					pointer tmp = allo.allocate(new_capacity);
					for (size_type i = 0; i < size(); ++i)
						allo.construct(tmp + i, _begin[i]);
					for (size_type i = 0; i < size(); ++i)
						allo.destroy(_begin + i);
					allo.deallocate(_begin, size());
					_begin = tmp;
					_end = _begin + n;
					_end_of_storage = _begin + new_capacity;

				}
				else
				{
					for (size_type i = size(); i < n; ++i)
						allo.construct(_begin + i, val);
					_end = _begin + n;
					_end_of_storage = _end;
				}
			}
		}
		bool empty() const
		{
			return size() == 0;
		}
		void reserve (size_type n)
		{
			if (n > capacity())
			{
				pointer tmp = allo.allocate(n);
				for (size_type i = 0; i < size(); ++i)
					allo.construct(tmp + i, _begin[i]);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				size_type new_size = size();
				_begin = tmp;
				_end = _begin + new_size;
				_end_of_storage = _begin + n;
			}
		}
		//element access
		reference operator[] (size_type n)
		{
			return _begin[n];
		}
		const_reference operator[] (size_type n) const
		{
			return _begin[n];
		}
		reference at (size_type n)
		{
			if (n >= size())
				throw std::out_of_range("out of range");
			return _begin[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("out of range");
			return _begin[n];
		}
		reference front()
		{
			return _begin[0];
		}
		const_reference front() const
		{
			return _begin[0];
		}
		reference back()
		{
			return _begin[size() - 1];
		}
		const_reference back() const
		{
			return _begin[size() - 1];
		}
		//modifier
		//______assign_______________________//
		template <class InputIterator>
  		void assign (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			size_type n = last - first;
			if (n > capacity())
			{
				pointer tmp = allo.allocate(n);
				for (size_type i = 0; i < n; ++i)
					allo.construct(tmp + i, first[i]);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + n;
				_end_of_storage = _end;
			}
			else
			{
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				_end = _begin + n;
				_end_of_storage = _end;
				for (size_type i = 0; i < size(); ++i)
					allo.construct(_begin + i, first[i]);
			}
		}
		void assign (size_type n, const value_type& val)
		{
			if (n > capacity())
			{
				pointer tmp = allo.allocate(n);
				for (size_type i = 0; i < n; ++i)
					allo.construct(tmp + i, val);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + n;
				_end_of_storage = _end;
			}
			else
			{
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				_end = _begin + n;
				_end_of_storage = _end;
				for (size_type i = 0; i < size(); ++i)
					allo.construct(_begin + i, val);
			}
		}
		void push_back (const value_type& val)
		{
			size_type new_size = size() + 1;
			if (new_size > capacity())
			{
				size_type new_capacity = capacity() * 2;
				pointer tmp = allo.allocate(new_capacity);
				for (size_type i = 0; i < size(); ++i)
					allo.construct(tmp + i, _begin[i]);
				allo.construct(tmp + size(), val);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + new_size;
				_end_of_storage = _begin + new_capacity;
			}
			else
			{
				allo.construct(_end, val);
				++_end;
			}
		}
		void pop_back()
		{
			allo.destroy(_end--);
		}
		void swap (vector& x)
		{
			std::swap(_begin, x._begin);
			std::swap(_end, x._end);
			std::swap(_end_of_storage, x._end_of_storage);
		}
		void clear()
		{
			for (size_type i = 0; i < size(); ++i)
				allo.destroy(_begin + i);
			_end = _begin;
		}
	private:
		Alloc allo;
		pointer _begin;
		pointer _end;
		pointer _end_of_storage;
	};
}
