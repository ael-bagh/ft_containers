#pragma once
#include "RB_tree.hpp"
#include "pair.hpp"

namespace ft
{


    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > 
    class map
    {
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const Key, T> value_type;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            class value_compare
            {
                friend class map;
                    Compare _Compare;
                public:
                    value_compare(const Compare& comp = Compare()) : _Compare(comp) {}
                    bool operator()(const value_type& lhs, const value_type& rhs) const
                    {
                        return _Compare(lhs.first, rhs.first);
                    }
            };
    };
}
