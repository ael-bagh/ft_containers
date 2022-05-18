#pragma once
#include "RB_tree.hpp"

namespace ft
{
    template<typename Key, typename Pair, typename Compare>
    class map_Comp
    {
        public:
            Compare cmp;
            map_Comp () : cmp(Compare()){}
            map_Comp(Compare cmp) : cmp(cmp) {}
            bool operator()(const Key& lhs, const Key& rhs) const
            {
                return cmp(lhs, rhs);
            }
            bool operator()(const Pair&lhs, const Key& rhs) const
            {
                return cmp(lhs.first, rhs);
            }
            bool operator()(const Key& lhs, const Pair& rhs) const
            {
                return cmp(lhs, rhs.first);
            }
            bool operator()(const Pair& lhs, const Pair& rhs) const
            {
                return cmp(lhs.first, rhs.first);
            }
    };
    
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
            typedef Compare key_compare;
            key_compare _Mt_cmp;
            key_compare key_comp() const
            {
                return _Mt_cmp;
            }
            value_compare value_comp() const
            {
                return value_compare(_Mt_cmp);
            }
        private:
            typedef ft::RB_tree<value_type, key_type ,map_Comp<key_type, value_type , key_compare> , allocator_type >RB_tree;
            RB_tree _tree;
        public:
            typedef typename RB_tree::iterator                  iterator;
            typedef typename RB_tree::const_iterator            const_iterator;
            typedef typename RB_tree::reverse_iterator          reverse_iterator;
            typedef typename RB_tree::const_reverse_iterator    const_reverse_iterator;
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
            iterator begin()
            {
                return _tree.begin();
            }
            const_iterator begin() const
            {
                return _tree.begin();
            }
            iterator end()
            {
                return _tree.end();
            }
            const_iterator end() const
            {
                return _tree.end();
            }
            reverse_iterator rbegin()
            {
                return _tree.rbegin();
            }
            const_reverse_iterator rbegin() const
            {
                return _tree.rbegin();
            }
            reverse_iterator rend()
            {
                return _tree.rend();
            }
            const_reverse_iterator rend() const
            {
                return _tree.rend();
            }
            ft::pair<iterator, bool> insert( const value_type& value )
            {
                return _tree.insert(value);
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
            iterator find( const Key& key )
            {
                return _tree.find_node(key);
            }
            const_iterator find( const Key& key ) const
            {
                return _tree.find_node(key);
            }
            void erase (iterator position)
            {
                _tree.erase(position);
            }
            size_type erase( const Key& key )
            {
                return _tree.erase(key);
            }
            void swap( map& other )
            {
                _tree.swap(other._tree);
            }
    };
    template<class Key, class T, class Compare, class Allocator>
    bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs== rhs;
    }
    template<class Key, class T, class Compare, class Allocator>
    bool operator!=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs== rhs);
    }
    template<class Key, class T, class Compare, class Allocator>
    bool operator<(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs< rhs;
    }
    template<class Key, class T, class Compare, class Allocator>
    bool operator<=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs< rhs;
    }
    template<class Key, class T, class Compare, class Allocator>
    bool operator>(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs< rhs;
    }
    template<class Key, class T, class Compare, class Allocator>
    bool operator>=(const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs< rhs;
    }
    template<class Key, class T, class Compare, class Allocator>
    void swap(ft::map<Key, T, Compare, Allocator>& lhs, ft::map<Key, T, Compare, Allocator>& rhs)
    {
        lhs.swap(rhs);
    }
}   

