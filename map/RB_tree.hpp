#pragma once
#include "pair.hpp"
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
    };

    template<class T, class Compare, class KeyOf,class Allocator > 
    class RB_tree
    {
    public:
        typedef node<T>             node_type;
        typedef node_type*          node_ptr;

        typedef T                   value_type;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef typename Allocator::template rebind<node_type>::other allocator_type;
        typedef Compare              key_compare;
        private:
            node_type       end_node;
            allocator_type  _allocator;
            key_compare     _compare;
            size_type       _size;

        public:

            node_ptr& root()
            {
                return end_node.left;
            }

            const node_ptr& nil() const
            {
                return end_node.parent;
            }

            RB_tree()
            {
                end_node.is_black = true;
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
            node_ptr& find_node(const T& value, node_ptr &parent)
            {
                parent = &end_node;
                node_ptr* current = &root();
                while(*current)
                {
                    if (_compare(KeyOf()(value), KeyOf()((*current)->value)))
                    {
                        parent = (*current);
                        current = &parent->left;
                    }
                    else if (_compare(KeyOf()((*current)->value), KeyOf()(value)))
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

            // TODO: return iterator
            ft::pair<node_ptr, bool> insert(const value_type& value)
            {
                node_ptr parent;
                node_ptr &current = find_node(value, parent);
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
            node_ptr minimum(node_ptr node)
            {
                while (node->left)
                    node = node->left;
                return node;
            }

            node_ptr maximum(node_ptr node)
            {
                while (node->right)
                    node = node->right;
                return node;
            }

            void remove(const value_type& value)
            {
                node_ptr parent;
                node_ptr &current = find_node(value, parent);
                if (!current)
                    return;
                remove(current);
            }

            void remove(node_ptr node)
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

                    // print the value of the node
                    if (node->is_black)
                    std::cout << node->value << std::endl;
                    else
                    std::cout << "\033[1;31m" << node->value << "\033[0m" << std::endl;

                    // enter the next tree level - left and right branch
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

            //successor of node
            node_ptr successor(node_ptr node)
            {
                if (node->right)
                    return minimum(node->right);
                node_ptr y = node->parent;
                while (y && node == y->right)
                {
                    node = y;
                    y = y->parent;
                }
                return y;
            }
            //predecessor of node
            node_ptr predecessor(node_ptr node)
            {
                if (node->left)
                    return maximum(node->left);
                node_ptr y = node->parent;
                while (y && node == y->left)
                {
                    node = y;
                    y = y->parent;
                }
                return y;
            }
    };
}

