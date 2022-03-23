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
		explicit vector(const allocator_type& alloc = allocator_type()):_size(0),  _begin(NULL), _capacity(0){}
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n) , _capacity(n)
		{
			_begin = allo.allocate(n);
			for (size_type i = 0; i < _size; i++)
				allo.construct(_begin + i, val);
		}
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				if (_size)
				{
					for (size_type i = 0; i < _size; i++)
						allo.destroy(_begin + i);
					allo.deallocate(_begin, _size);
				}
				_size = x._size;
				_capacity = x._capacity;
				_begin = allo.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_begin + i, x._begin[i]);
			}
			return *this;
		}
		reference operator[] (size_type n)
		{
			return *(_begin + n);
		}
		const_reference operator[] (size_type n) const
		{
			return *(_begin + n);
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
					allo.destroy(_begin + i);
				_capacity = _size;
				_size = n;
			}
			else
			{
				tmp = allo.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(tmp + i, _begin[i]);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(_begin + i);
				n < _size * 2 ? size = _size * 2 : size = n;
				allo.deallocate(_begin, _capacity);
				_begin  = allo.allocate(size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_begin + i, tmp[i]);
				for (size_type i = _size; i < size; i++)
					allo.construct(_begin + i, val);
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
					allo.construct(tmp + i, _begin[i]);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, _capacity);
				_begin  = allo.allocate(n);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_begin + i, tmp[i]);
				for (size_type i = _size; i < n; i++)
					allo.construct(_begin + i);
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
			return _begin[_size];
		}
		const_reference back() const
		{
			return _begin[_size];
		}
		void push_back (const value_type& val)
		{
			value_type *tmp;
			size_type size;
			if (_capacity > _size)
			{
				_begin[_size] = val;
				_size++;
			}
			else
			{
				tmp = allo.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(tmp + i, _begin[i]);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(_begin + i);
				size = _size * 2 > this->max_size() ? this->max_size() : _size * 2;
				if (_size == 0)
					size = 1;
				allo.deallocate(_begin, _capacity);
				_begin  = allo.allocate(size);
				for (size_type i = 0; i < _size; i++)
					allo.construct(_begin + i, tmp[i]);
				for (size_type i = _size; i < size; i++)
					allo.construct(_begin + i);
				for(size_type i = 0 ; i < _size; i++)
					allo.destroy(tmp + i);
				allo.deallocate(tmp, _size);
				_begin[_size] = val;
				_size++;
				_capacity = size;
			}
		}
		void pop_back()
		{
			if(_size)
			{
				allo.destroy( _begin + (_size - 1));
				_size--;
			}
		}
		void swap (vector& x)
		{
			vector y;
			y = x;
			x = *this;
			*this = y;
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				allo.destroy(_begin + i);
			_size = 0;
		}
	private:
		size_type _size;
		size_type _capacity;
		value_type *_begin;
	};
}
