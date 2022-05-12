#pragma once
namespace ft
{
    template <typename T>
    class node
    {
        typedef node<T> self_type;
        typedef T value_type;
        typedef self_type* node_ptr;
    private:
        node_ptr _parent;
        node_ptr _left;
        node_ptr _right;
        value_type _value;
        bool _is_black;
    public:
        node(): _parent(nullptr), _left(nullptr), _right(nullptr), _value(), _is_black(false) {} ;
        node(const value_type& value): _parent(nullptr), _left(nullptr), _right(nullptr), _value(value), _is_black(false) {} ;
        node(const value_type& value, bool is_black): _parent(nullptr), _left(nullptr), _right(nullptr), _value(value), _is_black(is_black) {} ;
        //copy constructor
        node(const self_type& other): _parent(other._parent), _left(other._left), _right(other._right), _value(other._value), _is_black(other._is_black) {} ;
        ~node() {} ;
        self_type& operator=(const self_type& other)
        {
            _parent = other._parent;
            _left = other._left;
            _right = other._right;
            _value = other._value;
            _is_black = other._is_black;
            return *this;
        }
        node_ptr& parent() { return _parent; }
        node_ptr& left() { return _left; }
        node_ptr& right() { return _right; }
        value_type& value() { return _value; }
        bool& is_black() { return _is_black; }
        ~node();
    };
}
