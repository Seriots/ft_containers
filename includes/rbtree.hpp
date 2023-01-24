/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:36:40 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/24 17:09:16 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "reverse_iterator.hpp"
#include "pair.hpp"

#include <iostream>

#define color_black false
#define color_red true

namespace ft
{
	template <class V>
	class node
	{
		public:
			typedef V			value_type;
		
		private:
			value_type			value;
			node<value_type>	*parent;
			node<value_type>	*left;
			node<value_type>	*right;
			bool				color;
			
		public:
			node() : value(), parent(NULL), left(NULL), right(NULL), color(color_black) {};
			node(const value_type& val) : value(val),  parent(NULL), left(NULL), right(NULL), color(color_black) {};
			~node() {};
			
			void	setValue(const value_type& val) { value = val; };
			void	setParent(node *p) { parent = p; };
			void	setLeft(node *l) { left = l; };
			void	setRight(node *r) { right = r; };
			void	setColor(bool c) { color = c; };

			value_type		getValue() const { return value; };
			node			*getParent() const { return parent; };
			node			*getLeft() const { return left; };
			node			*getRight() const { return right; };
			bool			getColor() const { return color; };

			void	display()
			{
				std::cout << this->getValue().first << "-";
				if (this->getColor() == color_red)
					std::cout << "red ::: ";
				else
					std::cout << "black ::: ";
				if (this->getParent() != NULL)
				{
					if (this->getParent()->getLeft() == this)
						std::cout << "left" << std::endl;
					else
						std::cout << "right" << std::endl;
				}
				else
					std::cout << "root" << std::endl;
				if (this->getLeft() != NULL)
					this->getLeft()->display();
				if (this->getRight() != NULL)
					this->getRight()->display();
			}
	};

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::node<ft::pair<const Key, T> > > >
	class rbTree
	{
		public:
			typedef Key				 							key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>					value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef pointer										iterator;
			typedef const_pointer								const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef node<value_type>							node_type;

		private:
			node_type			*_root;
			allocator_type		_allocator;
			size_type			_size;

			void __replaceParentsChild(node_type *parent, node_type *oldChild, node_type *newChild)
			{
				if (parent == NULL)
					_root = newChild;
				else if (parent->getLeft() == oldChild)
					parent->setLeft(newChild);
				else if (parent->getRight() == oldChild)
					parent->setRight(newChild);

				if (newChild != NULL)
					newChild->setParent(parent);
			}

			void	__rightRotation(node_type *node)
			{
				node_type	*parent = node->getParent();
				node_type	*leftChild = node->getLeft();
				
				node->setLeft(leftChild->getRight());
				
				if (leftChild->getRight() != NULL)
					leftChild->getRight()->setParent(node);
				leftChild->setRight(node);
				node->setParent(leftChild);
				__replaceParentsChild(parent, node, leftChild);
			};


			void	__leftRotation(node_type *node)
			{
				node_type	*parent = node->getParent();
				node_type	*rightChild = node->getRight();
				
				node->setRight(rightChild->getLeft());
				
				if (rightChild->getLeft() != NULL)
					rightChild->getLeft()->setParent(node);
				rightChild->setLeft(node);
				node->setParent(rightChild);
				__replaceParentsChild(parent, node, rightChild);
			};

			node_type	*__getUncle(node_type *node)
			{
				if (node->getParent() == NULL || node->getParent()->getParent() == NULL)
					return (NULL);
				if (node->getParent() == node->getParent()->getParent()->getLeft())
					return (node->getParent()->getParent()->getRight());
				else
					return (node->getParent()->getParent()->getLeft());
			}

			void	__balanceTree(node_type *node)
			{
				node_type	*grand_parent;
				node_type	*parent;
				node_type	*uncle;

				if (node == NULL)
					return ;
				parent = node->getParent();
				if (parent == NULL)
				{
					node->setColor(color_black);
					return ;
				}
				if (parent->getColor() == color_black)
					return ;
				
				grand_parent = parent->getParent();
				
				if (grand_parent == NULL)
				{
					parent->setColor(color_black);
					return ;
				}
				
				uncle = __getUncle(node);

				if (uncle != NULL && uncle->getColor() == color_red)
				{
					parent->setColor(color_black);
					uncle->setColor(color_black);
					grand_parent->setColor(color_red);
					__balanceTree(grand_parent);
				}
				else if ((uncle == NULL || uncle->getColor() == color_black) && parent->getRight() == node && grand_parent->getLeft() == parent)
				{
					__leftRotation(parent);
					__rightRotation(parent);
					node->setColor(color_black);
					node->getLeft()->setColor(color_red);
					node->getRight()->setColor(color_red);
				}
				else if ((uncle == NULL || uncle->getColor() == color_black) && parent->getLeft() == node && grand_parent->getRight() == parent)
				{
					__rightRotation(parent);
					__leftRotation(parent);
					node->setColor(color_black);
					node->getLeft()->setColor(color_red);
					node->getRight()->setColor(color_red);
				}
				else if ((uncle == NULL || uncle->getColor() == color_black) && parent->getRight() == node && grand_parent->getRight() == parent)
				{
					__leftRotation(grand_parent);
					parent->setColor(color_black);
					if (parent->getLeft() != NULL)
						parent->getLeft()->setColor(color_red);
				}
				else if ((uncle == NULL || uncle->getColor() == color_black) && parent->getLeft() == node && grand_parent->getLeft() == parent)
				{
					__rightRotation(grand_parent);
					parent->setColor(color_black);
					if (parent->getRight() != NULL)
						parent->getRight()->setColor(color_red);
				}
			}

		public:
			rbTree(): _root(NULL) {};
			~rbTree() {};

			std::pair<iterator, bool>	insert(const value_type& val)
			{
				node_type	*new_node;
				node_type	*tmp = _root;
				node_type	*parent = NULL;

				while (tmp != NULL)
				{
					parent = tmp;
					if (tmp->getValue().first > val.first)
						tmp = tmp->getLeft();
					else if (tmp->getValue().first < val.first)
						tmp = tmp->getRight();
					else
						return (std::pair<iterator, bool>(iterator(), false)); // key already exists
				}
				
				new_node = _allocator.allocate(1);
				_allocator.construct(new_node, node_type(val));
				new_node->setColor(color_red);
				
				if (parent == NULL)
					_root = new_node;
				else if (parent->getValue().first < val.first)
					parent->setRight(new_node);
				else
					parent->setLeft(new_node);
				new_node->setParent(parent);

				__balanceTree(new_node);
				_size++;
				return (std::pair<iterator, bool>(iterator(new_node), true));
			};

			node_type	find(const Key &key)
			{
				node_type *tmp = _root;

				while (tmp != NULL)
				{
					if (tmp->getValue().first == key)
						return (tmp);
					else if (tmp->getValue().first < key)
						tmp = tmp->getLeft();
					else
						tmp = tmp->getRight();
				}
				return (NULL);
			};

			void	remove()
			{
				
			};
			
			void	display() const
			{
				if (_root != NULL)
					_root->display();
			};
	};
}