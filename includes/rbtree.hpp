/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:36:40 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/25 22:51:52 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "reverse_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree_node.hpp"
#include "pair.hpp"

#include <iostream>
#include <cstring>
#include <memory>

#ifndef color_black
 #define color_black false
 #define color_red true
#endif

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::node<ft::pair<const Key, T> > > >
	class rbTree
	{
		public:
			typedef Key				 							key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::rbTreeIterator<value_type>				iterator;
			typedef ft::rbTreeIterator<const value_type>		const_iterator;			
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef node<value_type>							node_type;

		private:
			node_type			*_root;
			allocator_type		_allocator;
			size_type			_size;
			key_compare			_comp;

			node_type	*__setNodeValue(node_type *node, const value_type &val)
			{
				node_type	*newNode = _allocator.allocate(1);
				_allocator.construct(newNode, node_type(val));
				return (node);
			};
			
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
			};

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
			};

			node_type	*__getSibling(node_type *node)
			{
				if (node->getParent() == NULL)
					return (NULL);
				if (node == node->getParent()->getLeft())
					return (node->getParent()->getRight());
				else
					return (node->getParent()->getLeft());
			};

			void	__handleRedSibling(node_type *node, node_type *sibling)
			{
				sibling->setColor(color_black);
				node->getParent()->setColor(color_red);

				if (node == node->getParent()->getLeft())
					__leftRotation(node->getParent());
				else
					__rightRotation(node->getParent());
			};

			bool	__isBlack(node_type *node)
			{
				if (node == NULL)
					return (true);
				return (node->getColor() == color_black);
			};

			void	__balanceTreeInsert(node_type *node)
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
					__balanceTreeInsert(grand_parent);
				}
				else if (__isBlack(uncle) && parent->getRight() == node && grand_parent->getLeft() == parent)
				{
					__leftRotation(parent);
					__rightRotation(parent);
					node->setColor(color_black);
					node->getLeft()->setColor(color_red);
					node->getRight()->setColor(color_red);
				}
				else if (__isBlack(uncle) && parent->getLeft() == node && grand_parent->getRight() == parent)
				{
					__rightRotation(parent);
					__leftRotation(parent);
					node->setColor(color_black);
					node->getLeft()->setColor(color_red);
					node->getRight()->setColor(color_red);
				}
				else if (__isBlack(uncle) && parent->getRight() == node && grand_parent->getRight() == parent)
				{
					__leftRotation(grand_parent);
					parent->setColor(color_black);
					if (parent->getLeft() != NULL)
						parent->getLeft()->setColor(color_red);
				}
				else if (__isBlack(uncle) && parent->getLeft() == node && grand_parent->getLeft() == parent)
				{
					__rightRotation(grand_parent);
					parent->setColor(color_black);
					if (parent->getRight() != NULL)
						parent->getRight()->setColor(color_red);
				}
			};

			void	__balanceTreeDelete(node_type *node)
			{
				node_type	*sibling;
				node_type	*parent;
				bool		nodeIsLeftChild;

				/****************Case 1***********************/
				if (node == _root)
				{
					node->setColor(color_black);
					return;
				}
				parent = node->getParent();
				sibling = __getSibling(node);

				/****************Case 2***********************/
				if (sibling->getColor() == color_red) {
					__handleRedSibling(node, sibling);
					sibling = __getSibling(node);
				}

				if (__isBlack(sibling->getLeft()) && __isBlack(sibling->getRight()))
				{
					sibling->setColor(color_red);

					/****************Case 3***********************/
					if (parent->getColor() == color_red)
						parent->setColor(color_black);
					/****************Case 4***********************/
					else
						__balanceTreeDelete(parent);
				}
				else
				{
					nodeIsLeftChild = (node == parent->getLeft());

					/****************Case 5***********************/
					if (nodeIsLeftChild && __isBlack(sibling->getRight()))
					{
						sibling->getLeft()->setColor(color_black);
						sibling->setColor(color_red);
						__rightRotation(sibling);
						sibling = parent->getRight();
					}
					else if (!nodeIsLeftChild && __isBlack(sibling->getLeft()))
					{
						sibling->getRight()->setColor(color_black);
						sibling->setColor(color_red);
						__leftRotation(sibling);
						sibling = parent->getLeft();
					}

					/****************Case 6***********************/
					sibling->setColor(parent->getColor());
					parent->setColor(color_black);
					if (nodeIsLeftChild)
					{
						sibling->getRight()->setColor(color_black);
						__leftRotation(parent);
					}
					else
					{
						sibling->getLeft()->setColor(color_black);
						__rightRotation(parent);
					}
				}
			};
			
			node_type	*__removeWithZeroOrOneChild(node_type *node, bool color)
			{
				node_type	*ret;

				if (node->getLeft() != NULL)
				{
					__replaceParentsChild(node->getParent(), node, node->getLeft());
					ret = node->getLeft();
					_allocator.destroy(node);
					_allocator.deallocate(node, 1);
					return (ret);
				}
				else if (node->getRight() != NULL)
				{
					__replaceParentsChild(node->getParent(), node, node->getRight());
					ret = node->getRight();
					_allocator.destroy(node);
					_allocator.deallocate(node, 1);
					return (ret);
				}
				else
				{
					if (color == color_black)
					{
						node->setDelete(1);
						node->setColor(color_black);
						return (node);
					}
					else
					{
						__replaceParentsChild(node->getParent(), node, NULL); //delete node;
						_allocator.destroy(node);
						_allocator.deallocate(node, 1);
						return (NULL);
					}
				}
			};

			node_type	*__findMinimum(node_type *node)
			{
				if (node == NULL)
					return (NULL);
				while (node->getLeft() != NULL)
					node = node->getLeft();
				return (node);
			};

			node_type	*__findMaximum(node_type *node)
			{
				if (node == NULL)
					return (NULL);
				while (node->getRight() != NULL)
					node = node->getRight();
				return (node);
			};

		public:
			rbTree(): _root(NULL) {};
			~rbTree() {};

			iterator	begin()
			{
				return (iterator(__findMinimum(_root)));
			};

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(__findMaximum(_root)));
			};

			iterator	end()
			{
				return (iterator(__findMaximum(_root)));
			};

			reverse_iterator	rend()
			{
				return (reverse_iterator(__findMinimum(_root)));
			};

			std::pair<iterator, bool>	insert(const value_type& val)
			{
				node<value_type>	*new_node;
				node_type	*tmp = _root;
				node_type	*parent = NULL;

				while (tmp != NULL)
				{
					parent = tmp;
					if (_comp(val.first, tmp->getValue().first))
						tmp = tmp->getLeft();
					else if (_comp(tmp->getValue().first, val.first))
						tmp = tmp->getRight();
					else
						return (std::pair<iterator, bool>(iterator(), false)); // key already exists
				}
				
				new_node = _allocator.allocate(1);
				_allocator.construct(new_node, node_type(val));
				new_node->setColor(color_red);
				
				if (parent == NULL)
					_root = new_node;
				else if (_comp(parent->getValue().first, val.first))
					parent->setRight(new_node);
				else
					parent->setLeft(new_node);
				new_node->setParent(parent);

				__balanceTreeInsert(new_node);
				_size++;
				return (std::pair<iterator, bool>(iterator(new_node), true));
			};

			node_type	*find(const Key &key)
			{
				node_type *tmp = _root;

				while (tmp != NULL)
				{
					if (_comp(key, tmp->getValue().first))
						tmp = tmp->getLeft();
					else if (_comp(tmp->getValue().first, key))
						tmp = tmp->getRight();
					else
						return (tmp); // key already exists
				}
				return (NULL);
			};

			void	remove(const Key &key)
			{
				node_type	*node = find(key);
				node_type	*movedUpNode;
				node_type	*Successor;
				bool		deletedColor;

				if (node == NULL)
					return ;
				
				deletedColor = node->getColor();
				if (node->getLeft() == NULL || node->getRight() == NULL)
					movedUpNode = __removeWithZeroOrOneChild(node, deletedColor);
				else
				{
					//reverse in-order successor
					Successor = __findMaximum(node->getLeft()); // find the in-order successor __findMinimum(node->getRight());
					//node = __setNodeValue(node, Successor->getValue());
					_allocator.construct(node, node_type(Successor->getValue()));
					deletedColor = Successor->getColor();
					movedUpNode = __removeWithZeroOrOneChild(Successor, Successor->getColor());
				}

				if (deletedColor == color_black)
				{
					__balanceTreeDelete(movedUpNode);
					if (movedUpNode->getDelete() == 1)
					{
						__replaceParentsChild(movedUpNode->getParent(), movedUpNode, NULL);
						_allocator.destroy(movedUpNode);
						_allocator.deallocate(movedUpNode, 1);
					}
				}
				_size--;
			};
	};
}