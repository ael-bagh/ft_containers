#include <iostream>

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
		explicit vector(const allocator_type& alloc = allocator_type()):_size(0),  _array(NULL), _capacity(0){}
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n) , _capacity(n)
		{
			_array = allo.allocate(n);
			for (size_type i = 0; i < _size; i++)
				allo.construct(_array + i, val);
		}
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				if (_size)
				{
					for (size_type i = 0; i < _size; i++)
						allo.destroy(_array + i);
					allo.deallocate(_array, _size);
				}
				_size = x._size;
				_capacity = x._capacity;
				_array = allo.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_array + i, x._array[i]);
			}
			return *this;
		}
		reference operator[] (size_type n)
		{
			return *(_array + i);
		}
		const_reference operator[] (size_type n) const
		{
			return *(_array + i);
		}
		vector(const vector &x)
		{
			*this = x;
		}
		~vector()
		{
		}
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return allo.max_size();
		}
		void resize (size_type n, value_type val = value_type())
		{
			value_type *tmp;
			size_type size = 0;
			if (n <= _size)
			{
				for(size_type i = n + 1; i < _size; i++)
					allo.destroy(_array + i);
				_capacity = _size;
				_size = n;
			}
			else
			{
				tmp = allo.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(tmp + i, _array[i]);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(_array + i);
				n < _size * 2 ? size = _size * 2 : size = n;
				allo.deallocate(_array, _capacity);
				_array  = allo.allocate(size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_array + i, tmp[i]);
				for (size_type i = _size; i < size; i++)
					allo.construct(_array + i, val);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(tmp + i);
				allo.deallocate(tmp, _size);
				_size = n;		
				_capacity = size;
			}
		}
		size_type capacity()
		{
			return _capacity;
		}
		bool empty() const
		{
			return _size == 0 ? true :  false;
		}
		void reserve (size_type n)
		{
			value_type *tmp;
			if (n > _capacity)
			{
				tmp = allo.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(tmp + i, _array[i]);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(_array + i);
				allo.deallocate(_array, _capacity);
				_array  = allo.allocate(n);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_array + i, tmp[i]);
				for (size_type i = _size; i < n; i++)
					allo.construct(_array + i);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(tmp + i);
				allo.deallocate(tmp, _size);
				_capacity = n;
			}
		}
		reference at (size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _array[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _array[n];
		}
		reference front()
		{
			return _array[0];
		}
		const_reference front() const
		{
			return _array[0];
		}
		reference back()
		{
			return _array[_size];
		}
		const_reference back() const
		{
			return _array[_size];
		}
	private:
		size_type _size;
		size_type _capacity;
		value_type *_array;
	};
}
