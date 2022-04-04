#include <iostream>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		typedef T		value_type;
		typedef Alloc	allocator_type;
		typedef size_t	size_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

	public:
		explicit vector (const allocator_type& alloc = allocator_type()) : _size(0) , _begin(NULL), _end(NULL), _end_of_storage(NULL), allo(alloc){}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : allo(alloc)
		{
			_begin = allo.allocate(n);
			_end = _begin + n;
			_end_of_storage = _end;
			for (size_type i = 0; i < n; ++i)
				allo.construct(_begin + i, val);
			_size = n;
		}
		vector (const vector& x)
		{
			_begin = allo.allocate(x._size);
			_size = x._size;
			_end = _begin + _size;
			_end_of_storage = _end;
			for (size_type i = 0; i < _size; ++i)
				allo.construct(_begin + i, x._begin[i]);
		}
		~vector()
		{
			for (size_type i = 0; i < _size; ++i)
				allo.destroy(_begin + i);
			allo.deallocate(_begin, _size);
			_size  = 0;
			_begin = NULL;
			_end = NULL;
			_end_of_storage = NULL;
		}
		vector& operator= (const vector& x)
		{
			if (this != &x)
			{
				if (_size)
				{
					for (size_type i = 0; i < _size; ++i)
						allo.destroy(_begin + i);
					allo.deallocate(_begin, _size);
					_begin = allo.allocate(x._size);
					_size = x._size;
					_end = _begin + _size;
					_end_of_storage = _end;
					for (size_type i = 0; i < _size; ++i)
						allo.construct(_begin + i, x._begin[i]);
				}
			}
			return *this;
		}
		//capacity
		size_type size() const
		{
			return _size;
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
			if (n < _size)
			{
				for (size_type i = n; i < _size; ++i)
					allo.destroy(_begin + i);
				_size = n;
				_end_of_storage = _begin + _size + 1;
			}
			else
			{
				if (n > capacity())
				{
					size_type new_capacity = n < capacity() * 2 ? capacity() * 2 : n;
					pointer tmp = allo.allocate(new_capacity);
					for (size_type i = 0; i < _size; ++i)
						allo.construct(tmp + i, _begin[i]);
					for (size_type i = 0; i < _size; ++i)
						allo.destroy(_begin + i);
					allo.deallocate(_begin, _size);
					_begin = tmp;
					_end = _begin + n;
					_end_of_storage = _begin + new_capacity;
					_size = n;
				}
				else
				{
					for (size_type i = _size; i < n; ++i)
						allo.construct(_begin + i, val);
					_size = n;
					_end = _begin + n;
					_end_of_storage = _end;
				}
			}
		}
		bool empty() const
		{
			return _size == 0;
		}
		void reserve (size_type n)
		{
			if (n > capacity())
			{
				pointer tmp = allo.allocate(n);
				for (size_type i = 0; i < _size; ++i)
					allo.construct(tmp + i, _begin[i]);
				for (size_type i = 0; i < _size; ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, _size);
				_begin = tmp;
				_end = _begin + n;
				_end_of_storage = _end;
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
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _begin[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= _size)
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
			return _begin[_size - 1];
		}
		const_reference back() const
		{
			return _begin[_size - 1];
		}
		//modifier
		//______assign_______________________//
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last)
		{
			size_type n = last - first;
			if (n > capacity())
			{
				pointer tmp = allo.allocate(n);
				for (size_type i = 0; i < n; ++i)
					allo.construct(tmp + i, first[i]);
				for (size_type i = 0; i < _size; ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, _size);
				_begin = tmp;
				_end = _begin + n;
				_end_of_storage = _end;
				_size = n;
			}
			else
			{
				for (size_type i = 0; i < _size; ++i)
					allo.destroy(_begin + i);
				_size = n;
				_end = _begin + n;
				_end_of_storage = _end;
				for (size_type i = 0; i < _size; ++i)
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
				for (size_type i = 0; i < _size; ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, _size);
				_begin = tmp;
				_end = _begin + n;
				_end_of_storage = _end;
				_size = n;
			}
			else
			{
				for (size_type i = 0; i < _size; ++i)
					allo.destroy(_begin + i);
				_size = n;
				_end = _begin + n;
				_end_of_storage = _end;
				for (size_type i = 0; i < _size; ++i)
					allo.construct(_begin + i, val);
			}
		}
		void push_back (const value_type& val)
		{
			
		}
	private:
		Alloc allo;
		size_type _size;
		pointer _begin;
		pointer _end;
		pointer _end_of_storage;
	};
}
