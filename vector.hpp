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
				for (size_type i = 0; i < size(); ++i)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, capacity());
				_begin = allo.allocate(x.capacity());
				_end = _begin + x.size();
				_end_of_storage = _begin + x.capacity();
				for (size_type i = 0; i < x.size(); ++i)
					allo.construct(_begin + i, x._begin[i]);
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
			if (n > max_size())
				throw std::length_error("");
			if (n > capacity())
			{
				size_type new_capacity = ((n > capacity() * 2) ? n : capacity() * 2);
				pointer tmp = allo.allocate(new_capacity);
				size_type new_size = size();
				for (size_type i = 0; i < size(); i++)
					allo.construct(tmp + i, _begin[i]);
				for (size_type i = 0; i < size(); i++)
					allo.destroy(_begin + i);
				allo.deallocate(_begin, size());
				_begin = tmp;
				_end = _begin + new_size;
				_end_of_storage = _begin + new_capacity;
			}
		}
		void resize (size_type n, value_type val = value_type())
		{
			size_type old_size = size();
			if (n < old_size)
			{
				for (size_type i = n; i < size(); i++)
					allo.destroy(_begin + i);
			}
			else if (n > size())
			{
				if (n > capacity())
					reserve(n);
				for (size_type i = old_size; i < n; i++)
					allo.construct(_begin + i, val);
			}
			_end = _begin + n;
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
		void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			size_type	i;
			
			for(i = 0; i < size(); i++)
				allo.destroy(_begin + i);
			_end = _begin;
			do_assign(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
		}
		void assign (size_type n, const value_type& val)
		{
			size_type	i;

			if (n > max_size())
				throw(std::length_error(std::string("vector::assign")));
			for(i = 0; i < size(); i++)
				allo.destroy(_begin + i);
			if (n > capacity())
			{
				allo.deallocate(_begin, capacity());
				_begin = allo.allocate(n);
				_end_of_storage = _begin + n;
			}
			for (i = 0; i < n; i++)
				allo.construct(&_begin[i], val);
			_end = _begin + n;
		}
		void push_back (const value_type& val)
		{
			size_type new_size = size() + 1;
			if (new_size > capacity())
			{
				size_type new_capacity = (capacity())?capacity() * 2:1;
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
			size_type	diff = std::distance(this->begin(), position);
			insert(position, 1, val);
			return (this->begin() + diff);
		}
		// ? fill
		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type	newSize = n + size();
			size_type	newCapacity = newSize < (2 * capacity() ) ? (2 * capacity() ): newSize;
			size_type	firstPosition = std::distance(this->begin(), position);
			size_type	lastPosition = firstPosition + n;
			size_type	i;

			if (!n)
				return ;
			reserve(newSize > capacity() ? newCapacity : newSize);
			for(i = newSize - 1; i >= lastPosition; i--)
			{
				if (i >= size())
					allo.construct(&_begin[i], _begin[i - n]);
				else
					_begin[i] = _begin[i - n];
			}
			for (i = lastPosition; i > firstPosition; i--)
			{
				if (i >= size())
					allo.construct(&_begin[i - 1], val);
				else
					_begin[i - 1 ] = val;
			}
			_end = _begin + newSize;
		}
		//  ? range
		template <class InputIterator>
		void insert (iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			do_insert(position, first, last, typename std::iterator_traits<InputIterator>::iterator_category());
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
			size_type	start = first - this->begin();
			size_type	n = last - first;
			size_type	end = start + n;

			for(size_type i = 0; i < size() && end + i < size(); ++i)
				_begin[start + i] = _begin[end + i];
			for(size_type i = 0; i < n ; ++i)
				pop_back();
			return(first);
		}
		void clear()
		{
			erase(begin(), end());
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
		//assign
		template <class InputIterator>
		void do_assign (InputIterator first, InputIterator last, const std::forward_iterator_tag&)
		{
			size_type 	n;
			size_type	i;

			n = std::distance(first, last);
			if (capacity() < n)
			{
				_alloc.deallocate(_begin, capacity());
				_begin = allo.allocate(n);
				_capacity = n;
			}
			for (i = 0; i < n; i++)
				_alloc.construct(&_begin[i],*first++);
			_size = _begin + n;
		}
		template <class InputIterator>
		void do_assign (InputIterator first, InputIterator last, const std::input_iterator_tag&)
		{
			while(first != last)
				push_back(*first++);
		}
		//insertion
		template <class InputIterator>
		void do_insert (iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
		{
			size_type		n = 0;
			size_type		pos = std::distance(this->begin(), position);
			value_type		tmp;
				
			while(first != last)
			{
				push_back(*first++);
				n++;
			}
			for (size_type i = 0; i < n; i++)
			{
				tmp = _begin[pos + i];
				_begin[pos + i] = _begin[size() - n + i];
				_begin[size() - n + i] = tmp;
			}
		}
		template <class InputIterator>
		void do_insert (iterator position, InputIterator first, InputIterator last, const std::forward_iterator_tag&)
		{
			size_type	n = std::distance(first, last);
			size_type	newSize = n + size();
			size_type	firstPosition = std::distance(this->begin(), position);
			size_type	lastPosition = firstPosition + n;
				
			if (!n)
				return ;
			if(newSize > capacity())
			{
				pointer tmp;
				size_type newCapacity = newSize < (2 * capacity() ) ? (2 * capacity() ): newSize;
				size_type i = 0;
				try
				{
					tmp = allo.allocate(newCapacity);
					
					while(i < firstPosition)
					{
						allo.construct(tmp + i, _begin[i]);
						i++;
					}
					while(i < lastPosition)
					{
						allo.construct(tmp + i, *(first++));
						i++;
					}
					while(i < size() + n)
					{
						allo.construct(tmp + i, _begin[i - n]);
						i++;
					}
				}
				catch(...)
				{
					while(i-- > 0)
						allo.destroy(tmp + i);
					allo.deallocate(tmp, newCapacity);
					throw;
				}
				i = 0;
				while(i < size())
					allo.destroy(_begin + i++);
				allo.deallocate(_begin, capacity());
				_begin = tmp;
				_end = _begin + newSize;
				_end_of_storage = _begin + newCapacity;
			}
			else
			{
					vector tmp = *this;
					size_type i = firstPosition;
					while(i < lastPosition)
					{
						allo.construct(_begin + i, *(first++));
						i++;
					}
					while(i < size() + n)
					{
						allo.construct(_begin + i, tmp._begin[i - n]);
						i++;
					}
					_end = _begin + newSize;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////
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
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
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
