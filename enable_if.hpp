#pragma once //set value to true or false
namespace ft
{
	template <class T, T v>
	struct check 
	{
		static const  T value = v;
	};
	//typedef true or false type;
	typedef check<bool,true> true_type;
	typedef check<bool,false> false_type;
	//general enable_if
	template <bool Cond, class T = void> 
	struct enable_if;
	//specialization for false
	template <class T>
	struct enable_if<false, T> {};
	//specialization for true
	template <class T>
	struct enable_if<true, T>{typedef T type;};
	//non_integral types
	template <class T>
	struct is_integral : public false_type {};
	//integral types
	template <>
	struct is_integral<int> : public true_type {};
	template <>
	struct is_integral<bool> : public true_type {};
	template <>
	struct is_integral<char> : public true_type {};
	template <>
	struct is_integral<unsigned char> : public true_type {};
	template <>
	struct is_integral<short> : public true_type {};
	template <>
	struct is_integral<unsigned short> : public true_type {};
	template <>
	struct is_integral<long> : public true_type {};
	template <>
	struct is_integral<unsigned long> : public true_type {};
	template <>
	struct is_integral<long long> : public true_type {};
	template <>
	struct is_integral<unsigned long long> : public true_type {};
}