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
            typedef typename Allocator::template rebind<value_type>::other allocator_type;
            class value_compare
            {
                    Compare _Compare;
                public:
                    value_compare(const Compare& comp = Compare()) : _Compare(comp) {}
                    bool operator()(const value_type& lhs, const value_type& rhs) const
                    {
                        return _Compare(lhs.first, rhs.first);
                    }
            };
            typedef value_compare key_compare;
        private:
            typedef ft::RB_tree<key_type, value_type, value_compare, Allocator> RB_tree;
            RB_tree _tree;
        public:
            map() : _tree() {}
            explicit map( const Compare& comp, const Allocator& alloc = Allocator()) : _tree(comp, alloc) {}
            template< class InputIt >
            map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _tree(comp, alloc)
            {
                while (first != last)
                {
                    _tree.insert(*first);
                    ++first;
                }
            }
            map( const map& other ) : _tree(other._tree) {}
            ~map() {}
            map& operator=( const map& other )
            {
                _tree = other._tree;
                return *this;
            }
            allocator_type get_allocator() const
            {
                return _tree.get_allocator();
            }
            T& at( const Key& key )
            {
                if (end() == _tree.find_node(key))
                    throw std::out_of_range("ft::map::at");
                return _tree.find_node(key)->second;
            }

            const T& at( const Key& key ) const
            {
                if (end() == _tree.find_node(key))
                    throw std::out_of_range("ft::map::at");
                return _tree.find_node(key)->second;
            }
            T& operator[]( const Key& key )
            {
                return _tree.insert(value_type(key, T())).first->value.second;
            }
            bool empty() const
            {
                return _tree.empty();
            }
            size_type size() const
            {
                return _tree.size();
            }
            size_type max_size() const
            {
                return _tree.max_size();
            }
            void clear()
            {
                _tree.clear();
            }
            
    };
}
