#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
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
		typedef typename ft::iterator<value_type> iterator;
		typedef typename ft::iterator<const value_type> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		explicit vector (const allocator_type& alloc = allocator_type()) : allo(alloc) , _begin(NULL), _end(NULL), _end_of_storage(NULL){}
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
			typename ft::iterator_traits<InputIterator>::iterator_category cat;
			this->__internal_construct <InputIterator>(first, last, cat);
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
		void resize (size_type n, value_type val = value_type())
		{
			if (n < size())
			{
				for (size_type i = n; i < size(); ++i)
					allo.destroy(_begin + i);
				_end = _begin + n;
			}
			else if (n > size())
			{
				if (n > capacity())
					reserve(n);
				for (size_type i = size(); i < n; ++i)
					allo.construct(_begin + i, val);
				_end = _begin + n;
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
			typename ft::iterator_traits<InputIterator>::iterator_category cat;
			__internal_assign <InputIterator> (first, last, cat);
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
		iterator insert (iterator position, const value_type& val)
		{
			size_type n = position - _begin;
			size_type new_size = size() + 1;
			if (new_size > capacity())
			{
				size_type new_capacity = capacity() * 2;
				pointer tmp = allo.allocate(new_capacity);
				for (size_type i = 0; i < n; ++i)
					allo.construct(tmp + i, _begin[i]);
				allo.construct(tmp + n, val);
				for (size_type i = n; i < size(); ++i)
					allo.construct(tmp + i + 1, _begin[i]);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + new_size;
				_end_of_storage = _begin + new_capacity;
			}
			else
			{
				for (size_type i = size(); i > n; --i)
					allo.construct(_begin + i, _begin[i - 1]);
				allo.construct(_begin + n, val);
				++_end;
			}
			return _begin + n;
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type pos = position - _begin;
			size_type new_size = size() + n;
			if (new_size > capacity())
			{
				size_type new_capacity = capacity() * 2;
				pointer tmp = allo.allocate(new_capacity);
				for (size_type i = 0; i < pos; i++)
					allo.construct(tmp + i, _begin[i]);
				for (size_type i = pos; i < n + pos; i++)
					allo.construct(tmp + i, val);
				for (size_type i = pos + n; i < new_size; i++)
					allo.construct(tmp + i, _begin[i]);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + new_size;
				_end_of_storage = _begin + new_capacity;
			}
			else
			{
				for (size_type i = pos; i < new_size; i++)
					allo.construct(_begin + i + n, _begin[i]);
				for (size_type i = pos; i < n + pos; i++)
					allo.destroy(_begin + i);
				for (size_type i = pos; i < n + pos; i++)
					allo.construct(_begin + i, val);
				_end = _end + n;
			}
		}
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			size_type pos = position - _begin;
			size_type new_size = size() + std::distance(first, last);
			if (new_size > capacity())
			{
				size_type new_capacity = capacity() * 2;
				pointer tmp = allo.allocate(new_capacity);
				for (size_type i = 0; i < pos; i++)
					allo.construct(tmp + i, _begin[i]);
				for (InputIterator it = first; it != last; ++it)
					allo.construct(tmp + pos++, *it);
				for (size_type i = pos; i < size(); i++)
					allo.construct(tmp + i + std::distance(first, last), _begin[i]);
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + new_size;
				_end_of_storage = _begin + new_capacity;
			}
			else
			{
				for (size_type i = pos; i < new_size; i++)
					allo.construct(_begin + i + std::distance(first, last), _begin[i]);
				for (InputIterator it = first; it != last; ++it)
					allo.construct(_begin + pos++, *it);
				_end = _end + std::distance(first, last);
			}
		}
		iterator erase (iterator position)
		{
			size_type pos = position - _begin;
			for (size_type i = pos; i < size(); ++i)
				allo.destroy(_begin + i);
			for (size_type i = pos; i < size(); ++i)
				allo.construct(_begin + i, _begin[i + 1]);
			allo.destroy(_end--);
			return _begin + pos;
		}
		iterator erase (iterator first, iterator last)
		{
			size_type pos = first - _begin;
			for (size_type i = pos; i < size(); ++i)
				allo.destroy(_begin + i);
			for (size_type i = pos; i < size(); ++i)
				allo.construct(_begin + i, _begin[i + std::distance(first, last)]);
			allo.destroy(_end -= std::distance(first, last));
			return _begin + pos;
		}
		void clear()
		{
			for (size_type i = 0; i < size(); ++i)
				allo.destroy(_begin + i);
			_end = _begin;
		}
		allocator_type get_allocator() const
		{
			return allo;
		}
	private:
		Alloc allo;
		pointer _begin;
		pointer _end;
		pointer _end_of_storage;

		///////////////////////////////////////////////////////////////////////////////////////////
		template <class IT>
		void __internal_assign (IT first, IT last, std::input_iterator_tag)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		template <class IT>
		void __internal_assign (IT first, IT last, std::forward_iterator_tag)
		{
			size_type n = std::distance(first, last);
			if (n > capacity())
			{
				pointer tmp = allo.allocate(n);
				for (size_type i = 0; i < n; i++)
					allo.construct(tmp + i, *first++);
				for (size_type i = 0; i < size(); i++)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + n;
				_end_of_storage = _end;
			}
			else
			{
				for (size_type i = 0; i < size(); i++)
					allo.destroy(_begin + i);
				_end = _begin + n;
				_end_of_storage = _end;
				for (size_type i = 0; i < size(); i++)
					allo.construct(_begin + i, *first++);
			}
		}
		template <class IT>
		void __internal_construct (IT first, IT last, std::input_iterator_tag)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		template <class IT>
		void __internal_construct (IT first, IT last, std::forward_iterator_tag)
		{
			size_type n = std::distance(first, last);

			_begin = allo.allocate(n);
			_end = _begin + n;
			_end_of_storage = _end;
			for (size_type i = 0; i < n; i++)
				allo.construct(_begin + i, *first++);
		}
	};
	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	template <class T, class Alloc>
  	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
  	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
	  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
  	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
	  return !(rhs < lhs);
	}	
	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
	  return rhs < lhs;
	}		
	template <class T, class Alloc>
  	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
	  return !(lhs < rhs);
	}
}
