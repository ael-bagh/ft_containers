#pragma once
#include "../pair.hpp"
#include "bidirectional_iterator.hpp"
#include "../reverse_iterator.hpp"
namespace ft
{
    template<class T>   
    struct node 
    {
        node    *left;
        node    *right;
        node    *parent;
        T       value;
        bool    is_black;
        bool    is_nil;
        node()
        {
            left = NULL;
            right = NULL;
            parent = NULL;
            is_black = false;
            is_nil = false;
        }
        node (T v): value(v)
        {
            left = NULL;
            right = NULL;
            parent = NULL;
            is_black = false;
            is_nil = false;
        }
        node & operator=(const node & n)
        {
            left = n.left;
            right = n.right;
            parent = n.parent;
            is_black = n.is_black;
            is_nil = n.is_nil;
            value = n.value;
            return *this;
        }
    };

    template<class T>
    node<T>* minimum(node<T>* node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    template<class T>
    node<T>* maximum(node<T>* node)
    {
        while (node->right)
            node = node->right;
        return node;
    }

    //successor of node
    template<class T>
    node<T>* successor(const node<T>* nd)
    {
        if (nd->right) {
            node<T>* tmp = nd->right;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }
        node<T>* y = nd->parent;
        while (y && nd == y->right)
        {
            nd = y;
            y = y->parent;
        }
        return y;
    }
    //predecessor of node
    template<class T>
    node<T>* predecessor(const node<T>* nd)
    {
        if (nd->left)
        {
            node<T>* tmp = nd->left;
            while (tmp->right)
                tmp = tmp->right;
            return tmp;
        }
        node<T>* y = nd->parent;
        while (y && nd == y->left)
        {
            nd = y;
            y = y->parent;
        }
        return y;
    }
    template<class T, class key , class Compare, class Allocator > 
    class RB_tree
    {
    public:
        typedef node<T>             node_type;
        typedef node_type*          node_ptr;
        typedef T                   value_type;
        typedef key                 key_type;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef typename Allocator::template rebind<node_type>::other allocator_type;
        typedef typename ft::bidirectional_iterator<value_type> iterator;
        typedef typename ft::const_bidirectional_iterator<value_type> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef Compare              key_compare;
        private:
            node_type       end_node;
            allocator_type  _allocator;
            key_compare     _compare;
            size_type       _size;

        public:

            const node_ptr& root() const
            {
                return end_node.left;
            }
            node_ptr& root()
            {
                return end_node.left;
            }
            const node_ptr& nil() const
            {
                return end_node.parent;
            }
            RB_tree & operator=(const RB_tree & x)
            {
                if (this != &x)
                {
                    _allocator = x._allocator;
                    _compare = x._compare;
                    clear();
                    insert(x.begin(), x.end());
                }
                return *this;
            }

            RB_tree() : _compare(Compare())
            {
                end_node.is_black = true;
                _size = 0;
            }
            RB_tree(const key_compare& comp , const allocator_type& alloc) : _allocator(alloc), _compare(comp)
            {
                end_node.is_black = true;
                _size = 0;
            }
            RB_tree(const RB_tree & x) : _allocator(x._allocator), _compare(x._compare)
            {
                end_node.is_black = true;
                _size = 0;
                insert(x.begin(), x.end());
            }
            ~RB_tree()
            {

            }

            size_type size() const
            {
                return _size;
            }
            bool empty() const
            {
                return _size == 0;
            }
            size_type   max_size() const
            {
                return _allocator.max_size();
            }
            node_ptr& find_node_parent(const T& value, node_ptr &parent)
            {
                parent = &end_node;
                node_ptr* current = &root();
                while(*current)
                {
                    if (_compare((value), ((*current)->value)))
                    {
                        parent = (*current);
                        current = &parent->left;
                    }
                    else if (_compare((*current)->value, (value)))
                    {
                        parent = (*current);
                        current = &parent->right;
                    }
                    else
                        return (*current);
                }
                return (*current);
            }

            bool    is_black(node_ptr n)
            {
                return !n || n->is_black;
            }

            template <typename InputIterator>
            void    insert(InputIterator first, InputIterator last)
            {
                while (first != last)
                    insert(*++first);
            }
            // TODO: return iterator
            ft::pair<node_ptr, bool> insert(const value_type& value)
            {
                node_ptr parent;
                node_ptr &current = find_node_parent(value, parent);
                if (current)
                    return ft::pair<node_ptr, bool>(current, false);
                current = _allocator.allocate(1);
                _allocator.construct(current, value);
                _size++;
                current->parent = parent;
                fix_insert(current);
                return ft::pair<node_ptr, bool>(current, true);
            }
            void    fix_insert(node_ptr node)
            {
                while (!is_black(node->parent))
                {
                    if (node->parent == node->parent->parent->left)
                    {
                        node_ptr uncle = node->parent->parent->right;
                        if (!is_black(uncle))
                        {
                            node->parent->is_black = true;
                            uncle->is_black = true;
                            node->parent->parent->is_black = false;
                            node = node->parent->parent;
                        }
                        else
                        {
                            if (node == node->parent->right)
                            {
                                node = node->parent;
                                left_rotate(node);
                            }
                            node->parent->is_black = true;
                            node->parent->parent->is_black = false;
                            right_rotate(node->parent->parent);
                        }
                    }
                    else
                    {
                        node_ptr uncle = node->parent->parent->left;
                        if (!is_black(uncle))
                        {
                            node->parent->is_black = true;
                            uncle->is_black = true;
                            node->parent->parent->is_black = false;
                            node = node->parent->parent;
                        }
                        else
                        {
                            if (node == node->parent->left)
                            {
                                node = node->parent;
                                right_rotate(node);
                            }
                            node->parent->is_black = true;
                            node->parent->parent->is_black = false;
                            left_rotate(node->parent->parent);
                        }
                    }
                }
                root()->is_black = true;
            }   

            void transplant(node_ptr u, node_ptr v)
            {
                if (!u->parent)
                    root() = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;
                if (v)
                    v->parent = u->parent;
            
            }

            template <typename InputIterator>
            void    remove(InputIterator first, InputIterator last)
            {
                while (first != last)
                    remove(*++first);
            }

            void remove(const value_type& value)
            {
                node_ptr parent;
                node_ptr &current = find_node_parent(value, parent);
                if (!current)
                    return;
                rm(current);
            }

            void rm(node_ptr node)
            {

                bool original_color = node->is_black;
                node_ptr y = node;
                node_ptr x;
                node_ptr x_parent;
                _size--;
                if (!node->left)
                {
                    x_parent = node->parent;
                    x = node->right;
                    transplant(node, node->right);
                }
                else if (!node->right)
                {
                    x_parent = node->parent;
                    x = node->left;
                    transplant(node, node->left);
                }
                else
                {
                    y = minimum(node->right);
                    original_color = y->is_black;
                    x = y->right;
                    x_parent = y->parent;
                    if (y->parent == node)
                    {
                        x_parent = y;
                        if (x)  x->parent = y;
                    }
                    else
                    {
                        transplant(y, y->right);
                        y->right = node->right;
                        if (y->right)
                            y->right->parent = y;
                    }
                    transplant(node, y);
                    y->left = node->left;
                    if (y->left)
                        y->left->parent = y;
                    y->is_black = node->is_black;
                }

                if (original_color && _size)
                    fix_delete(x, x_parent);
            }
            void clear()
            {
                remove(begin(), end());
                root() = NULL;
                _size = 0;
            }
            void fix_delete(node_ptr node, node_ptr parent)
            {
                while (node != root() && is_black(node))
                {
                    if (node == (node ? node->parent : parent)->left)
                    {
                        node_ptr sibling = (node ? node->parent : parent)->right;
                        if (!is_black(sibling))
                        {
                            if (sibling)
                                sibling->is_black = true;
                            (node ? node->parent : parent)->is_black = false;
                            left_rotate((node ? node->parent : parent));
                            sibling = (node ? node->parent : parent)->right;
                        }
                        if (is_black(sibling->left) && is_black(sibling->right))
                        {
                            sibling->is_black = false;
                            node = (node ? node->parent : parent);
                        }
                        else
                        {
                            if (is_black(sibling->right))
                            {
                                sibling->left->is_black = true;
                                right_rotate(sibling);
                                sibling = (node ? node->parent : parent)->right;
                            }
                            sibling->is_black = (node ? node->parent : parent)->is_black;
                            (node ? node->parent : parent)->is_black = true;
                            sibling->right->is_black = true;
                            left_rotate((node ? node->parent : parent));
                            node = root();
                        }
                    }
                    else
                    {
                        node_ptr sibling = (node ? node->parent : parent)->left;
                        if (!is_black(sibling))
                        {
                            sibling->is_black = true;
                            (node ? node->parent : parent)->is_black = false;
                            right_rotate((node ? node->parent : parent));
                            sibling = (node ? node->parent : parent)->left;
                        }
                        if (is_black(sibling->left) && is_black(sibling->right))
                        {
                            sibling->is_black = false;
                            node = (node ? node->parent : parent);
                        }
                        else
                        {
                            if (is_black(sibling->left))
                            {
                                sibling->right->is_black = true;
                                left_rotate(sibling);
                                sibling = (node ? node->parent : parent)->left;
                            }
                            sibling->is_black = (node ? node->parent : parent)->is_black;
                            (node ? node->parent : parent)->is_black = true;
                            sibling->left->is_black = true;
                            right_rotate((node ? node->parent : parent));
                            node = root();
                        }
                    }
                }
                node->is_black = true;
            }



            void printBT(const std::string& prefix, const node_ptr node, bool isLeft)
            {
                if( node != nullptr )
                {
                    std::cout << prefix;
                    std::cout << (isLeft ? "├──" : "└──" );
                    if (node->is_black)
                        std::cout << node->value << std::endl;
                    else
                        std::cout << "\033[1;31m" << node->value << "\033[0m" << std::endl;
                    printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
                    printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
                }
            }

            void printBT(const node_ptr node)
            {
                printBT("", node, false);    
            }

            void printBT()
            {
                printBT(root());
            }
            void left_rotate(node_ptr x)
            {
                node_ptr y = x->right;
                x->right = y->left;
                if (y->left)
                    y->left->parent = x;
                y->parent = x->parent;
                if (!x->parent)
                    root() = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
            }

            void right_rotate(node_ptr x)
            {
                node_ptr y = x->left;
                x->left = y->right;
                if (y->right)
                    y->right->parent = x;
                y->parent = x->parent;
                if (!x->parent)
                    root() = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
                y->right = x;
                x->parent = y;
            }
            iterator begin()
            {
                if (root())
                    return iterator(minimum(root()));
                return iterator(&end_node);
            }
            iterator end()
            {
                return iterator(&end_node);
            }
            const_iterator begin() const
            {
                if (root())
                    return const_iterator(minimum(root()));
                return const_iterator(&end_node);
            }
            const_iterator end() const
            {
                return const_iterator(&end_node);
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            void erase (iterator position)
            {
                remove(position.node);
            }
            size_type erase (const key_type& k)
            {
                node_ptr node = find(k);
                if (node)
                {
                    erase(iterator(node));
                    return 1;
                }
                return 0;
            }

    };
    template<class T, class key , class Compare, class Allocator> 
    bool operator==(const RB_tree<T,key,Compare,Allocator>& lhs, const RB_tree<T,key,Compare,Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (typename RB_tree<T,key,Compare,Allocator>::iterator it = lhs.begin(); it != lhs.end(); ++it)
        {
            if (rhs.find(*it) == rhs.end())
                return false;
        }
        return true;
    }
    template<class T, class key , class Compare, class Allocator>
    bool operator!=(const RB_tree<T,key,Compare,Allocator> & lhs, const RB_tree<T,key,Compare,Allocator>& rhs)
    {
        return !(lhs == rhs);
    }
    template<class T, class key , class Compare, class Allocator> 
    bool operator<(const RB_tree<T,key,Compare,Allocator>& lhs, const RB_tree<T,key,Compare,Allocator>& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template<class T, class key , class Compare, class Allocator> 
    bool operator<=(const RB_tree<T,key,Compare,Allocator>& lhs, const RB_tree<T,key,Compare,Allocator>& rhs)
    {
        return !(rhs < lhs);
    }
    template<class T, class key , class Compare, class Allocator>
    bool operator>(const RB_tree<T,key,Compare,Allocator>& lhs, const RB_tree<T,key,Compare,Allocator>& rhs)
    {
        return rhs < lhs;
    }
    template<class T, class key , class Compare, class Allocator> 
    bool operator>=(const RB_tree<T,key,Compare,Allocator>& lhs, const RB_tree<T,key,Compare,Allocator>& rhs)
    {
        return !(lhs < rhs);
    }
}

