/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTreeSet.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:01:16 by lgiband           #+#    #+#             */
/*   Updated: 2023/02/03 11:12:24 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "reverse_iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree_node.hpp"
#include "pair.hpp"
#include "equal.hpp"

#include <iostream>
#include <cstring>
#include <memory>

#ifndef color_black
 #define color_black false
 #define color_red true
#endif

namespace ft
{
	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class rbTreeSet
	{
		public:
			typedef Key											key_type;
			typedef Key											value_type;
			typedef Compare										key_compare;
			typedef node<value_type>							node_type;
			typedef typename Allocator::template rebind<node_type>::other	allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::rbTreeIterator<const value_type, node_type>		iterator;
			typedef ft::rbTreeIterator<const value_type, node_type>		const_iterator;		
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;

		private:
			node_type			*_root;
			node_type			*_end;
			allocator_type		_allocator;
			size_type			_size;
			key_compare			_comp;

			void	__setNodeValue(node_type *node, const value_type &val)
			{
				node_type	tmp;

				tmp.setParent(node->getParent());
				tmp.setLeft(node->getLeft());
				tmp.setRight(node->getRight());
				tmp.setColor(node->getColor());
				_allocator.destroy(node);
				_allocator.construct(node, node_type(val));
				node->setParent(tmp.getParent());
				node->setLeft(tmp.getLeft());
				node->setRight(tmp.getRight());
				node->setColor(tmp.getColor());
			};

			void	__linkEnd(node_type *node)
			{
				if (node == NULL)
				{
					_allocator.destroy(_end);
					_allocator.construct(_end, value_type());
					return ;
				}
				_allocator.destroy(_end);
				_allocator.construct(_end, node->getValue());
				_end->setParent(NULL);
				_end->setRight(node);
				_end->setLeft(node);
				node->setParent(_end);
			};
			
			void __replaceParentsChild(node_type *parent, node_type *oldChild, node_type *newChild)
			{
				if (parent == _end)
				{
					_root = newChild;
				}
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
				if (node->getParent() == NULL || node->getParent() == _end)
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

			bool	__isBlack(node_type *node) const
			{
				if (node == NULL || node == _end)
					return (true);
				return (node->getColor() == color_black);
			};

			void	__balanceTreeInsert(node_type *node)
			{
				node_type	*grand_parent;
				node_type	*parent;
				node_type	*uncle;

				if (node == NULL || node == _end)
					return ;
				if (node == _root)
				{
					node->setColor(color_black);
					return ;
				}
				parent = node->getParent();
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
					__rightRotation(node->getParent());
					node->setColor(color_black);
					node->getLeft()->setColor(color_red);
					node->getRight()->setColor(color_red);
				}
				else if (__isBlack(uncle) && parent->getLeft() == node && grand_parent->getRight() == parent)
				{
					__rightRotation(parent);
					
					__leftRotation(node->getParent());
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
				bool		nodeIsLeftChild;

				/****************Case 1***********************/
				if (node == _root)
				{
					node->setColor(color_black);
					return;
				}

				sibling = __getSibling(node);

				/****************Case 2***********************/
				if (sibling->getColor() == color_red)
				{
					__handleRedSibling(node, sibling);
					sibling = __getSibling(node);
				}
				if (__isBlack(sibling->getLeft()) && __isBlack(sibling->getRight()))
				{
					sibling->setColor(color_red);
					
					/****************Case 3***********************/
					if (node->getParent()->getColor() == color_red)
						node->getParent()->setColor(color_black);
					/****************Case 4***********************/
					else
						__balanceTreeDelete(node->getParent());
				}
				else
				{
					nodeIsLeftChild = (node == node->getParent()->getLeft());

					/****************Case 5***********************/
					if (nodeIsLeftChild && __isBlack(sibling->getRight()))
					{
						sibling->getLeft()->setColor(color_black);
						sibling->setColor(color_red);
						__rightRotation(sibling);
						sibling = node->getParent()->getRight();
					}
					else if (!nodeIsLeftChild && __isBlack(sibling->getLeft()))
					{
						sibling->getRight()->setColor(color_black);
						sibling->setColor(color_red);
						__leftRotation(sibling);
						sibling = node->getParent()->getLeft();
					}

					/****************Case 6***********************/
					sibling->setColor(node->getParent()->getColor());
					node->getParent()->setColor(color_black);
					if (nodeIsLeftChild)
					{
						sibling->getRight()->setColor(color_black);
						__leftRotation(node->getParent());
					}
					else
					{
						sibling->getLeft()->setColor(color_black);
						__rightRotation(node->getParent());
					}
				}
			};
			
			node_type	*__removeZeroOrOneChild(node_type *node, bool color)
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

			node_type	*__findMinimum(node_type *node) const
			{
				if (node == NULL)// || node == _end
					return (NULL);
				while (node->getLeft() != NULL)
					node = node->getLeft();
				return (node);
			};

			node_type	*__findMaximum(node_type *node) const
			{
				if (node == NULL)// || node == _end
					return (NULL);
				while (node->getRight() != NULL)
					node = node->getRight();
				return (node);
			};

			void	__buildTree(node_type *from, node_type *to)
			{
				node_type	*tmp;
				bool		color;

				tmp = to->getParent();
				color = to->getColor();
				_allocator.construct(to, from->getValue());
				to->setParent(tmp);
				to->setColor(color);
				if (from->getLeft() != NULL)
				{
					to->setLeft(_allocator.allocate(1));
					to->getLeft()->setParent(to);
					to->getLeft()->setColor(from->getLeft()->getColor());
					__buildTree(from->getLeft(), to->getLeft());
				}
				if (from->getRight() != NULL)
				{
					to->setRight(_allocator.allocate(1));
					to->getRight()->setParent(to);
					to->getRight()->setColor(from->getRight()->getColor());
					__buildTree(from->getRight(), to->getRight());
				}
			};

			void	__clearTree(node_type *node)
			{
				if (node == NULL)
					return ;
				__clearTree(node->getLeft());
				__clearTree(node->getRight());
				_allocator.destroy(node);
				_allocator.deallocate(node, 1);
			};

			bool	__isEqual(node_type *node1, node_type *node2) const
			{
				if (node1 == NULL && node2 == NULL)
					return (true);
				if (node1 == NULL || node2 == NULL)
					return (false);
				if (node1->getValue() != node2->getValue())
					return (false);
				if (!__isEqual(node1->getLeft(), node2->getLeft()))
					return (false);
				if (!__isEqual(node1->getRight(), node2->getRight()))
					return (false);
				return (true);
			};

		public:
			rbTreeSet(): _root(NULL), _end(0), _allocator(allocator_type()), _size(0), _comp(Compare()) {_end = _allocator.allocate(1); _allocator.construct(_end, node_type());};
			
			rbTreeSet(rbTreeSet const &other): _root(NULL), _end(0), _allocator(other.get_allocator()), _size(other.size()), _comp(Compare())
			{
				if (this != &other)
				{
					_end = _allocator.allocate(1);
					_allocator.construct(_end, node_type());
					_size = other.size();
					if (other.getRoot() == NULL)
						return ;
					_root = _allocator.allocate(1);
					__buildTree(other.getRoot(), _root);
					__linkEnd(_root);
				}
			};

			rbTreeSet	&operator=(rbTreeSet const &other)
			{
				if (this != &other)
				{
					_allocator.destroy(_end);
					_allocator.construct(_end, node_type());
					__clearTree(_root);
					_root = NULL;
					_size = other.size();
					if (other.getRoot() == NULL)
						return (*this);
					_root = _allocator.allocate(1);
					__buildTree(other.getRoot(), _root);
					__linkEnd(_root);
				}
				return (*this);
			};
			
			
			~rbTreeSet() { _allocator.destroy(_end); _allocator.deallocate(_end, 1); __clearTree(_root); };

			iterator			begin() {return ((_size == 0 || _root == NULL) ? iterator(_end) : iterator(__findMinimum(_root)));};
			const_iterator		begin() const {return ((_size == 0 || _root == NULL) ? const_iterator(_end) : const_iterator(__findMinimum(_root)));};

			reverse_iterator	rbegin() { return (reverse_iterator(_end)); };
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_end)); };

			iterator			end() { return (iterator(_end)); };
			const_iterator		end() const { return (const_iterator(_end)); };

			reverse_iterator	rend() {return (_size == 0 || _root == NULL) ? reverse_iterator(_end) : reverse_iterator(__findMinimum(_root));};
			const_reverse_iterator	rend() const {return (_size == 0 || _root == NULL) ? const_reverse_iterator(_end) : const_reverse_iterator(__findMinimum(_root));};

			allocator_type		get_allocator() const { return (_allocator); };
			size_type			size() const { return (_size); };
			bool				empty() const { return (_size == 0); };
			size_type			max_size() const { return (_allocator.max_size()); };
			node_type			*getRoot() const { return (_root); };
			Compare				getComp() const { return (_comp); };
			void				setRoot(node_type *root) { _root = root; };
			void				setSize(size_type size) { _size = size; };
			void				setComp(Compare comp) { _comp = comp; };
			void				setAllocator(allocator_type allocator) { _allocator = allocator; };
			
			ft::pair<iterator, bool>	insert(const value_type& val)
			{
				node<value_type>	*new_node;
				node_type	*tmp = _root;
				node_type	*parent = NULL;

				while (tmp != NULL)
				{
					parent = tmp;
					if (_comp(val, tmp->getValue()))
						tmp = tmp->getLeft();
					else if (_comp(tmp->getValue(), val))
						tmp = tmp->getRight();
					else
						return (ft::pair<iterator, bool>(iterator(tmp), false)); // key already exists
				}
				new_node = _allocator.allocate(1);
				_allocator.construct(new_node, node_type(val));
				new_node->setColor(color_red);
				
				if (_root == NULL)
					_root = new_node;
				else if (_comp(parent->getValue(), val))
					parent->setRight(new_node);
				else
					parent->setLeft(new_node);
				new_node->setParent(parent);
				__balanceTreeInsert(new_node);
				
				_size++;
				__linkEnd(_root);
				return (ft::pair<iterator, bool>(iterator(new_node), true));
			};

			iterator	insert(iterator pos, const value_type& val)
			{
				(void)pos;
				node<value_type>	*new_node;
				node_type	*tmp = _root;
				node_type	*parent = NULL;

				while (tmp != NULL)
				{
					parent = tmp;
					if (_comp(val, tmp->getValue()))
						tmp = tmp->getLeft();
					else if (_comp(tmp->getValue(), val))
						tmp = tmp->getRight();
					else
						return (iterator(tmp)); // key already exists
				}
				
				new_node = _allocator.allocate(1);
				_allocator.construct(new_node, node_type(val));
				new_node->setColor(color_red);
				
				if (_root == NULL)
					_root = new_node;
				else if (_comp(parent->getValue(), val))
					parent->setRight(new_node);
				else
					parent->setLeft(new_node);
				new_node->setParent(parent);

				__balanceTreeInsert(new_node);
				_size++;
				__linkEnd(_root);
				return (iterator(new_node));
			};


			size_type	remove(const Key &key)
			{
				node_type	*node = find(key);
				node_type	*movedUpNode;
				node_type	*successor;
				bool		deletedColor;

				if (node == NULL || node == _end)
					return (0);
				
				deletedColor = node->getColor();
				if (node->getLeft() == NULL || node->getRight() == NULL)
				{
					movedUpNode = __removeZeroOrOneChild(node, deletedColor);
				}
				else
				{
					//reverse in-order successor 
					successor = __findMaximum(node->getLeft()); // find the in-order successor __findMinimum(node->getRight());
					__setNodeValue(node, successor->getValue());
					deletedColor = successor->getColor();
					movedUpNode = __removeZeroOrOneChild(successor, successor->getColor());
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
				__linkEnd(_root);
				_size--;
				return (1);
			};

			iterator	remove(iterator pos)
			{
				node_type	*node = find(*pos);
				iterator	ret = pos++;
				node_type	*movedUpNode;
				node_type	*successor;
				bool		deletedColor;

				if (node == NULL || node == _end)
				{
					return (iterator(_end));
				}
				deletedColor = node->getColor();
				if (node->getLeft() == NULL || node->getRight() == NULL)
				{
					movedUpNode = __removeZeroOrOneChild(node, deletedColor);
				}
				else
				{
					//reverse in-order successor 
					successor = __findMaximum(node->getLeft()); // find the in-order successor __findMinimum(node->getRight());
					__setNodeValue(node, successor->getValue());
					deletedColor = successor->getColor();
					movedUpNode = __removeZeroOrOneChild(successor, successor->getColor());
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
				__linkEnd(_root);
				_size--;
				return (ret);
			};

			node_type	*find(const Key &key) const
			{
				node_type *tmp = _root;

				while (tmp != NULL)
				{
					if (_comp(key, tmp->getValue()))
						tmp = tmp->getLeft();
					else if (_comp(tmp->getValue(), key))
						tmp = tmp->getRight();
					else
						return (tmp); // key already exists
				}
				return (NULL);
			};
			
			void	clear()
			{
				__clearTree(_root);
				_root = NULL;
				_size = 0;
			};

			void	swap(rbTreeSet &other)
			{
				node_type	*tmp = _root;
				node_type	*tmp_end = _end;
				size_type	tmp_size = _size;
				allocator_type	tmp_alloc = _allocator;
				key_compare	tmp_comp = _comp;
				

				_root = other._root;
				_end = other._end;
				_size = other.size();
				_allocator = other.get_allocator();
				_comp = other._comp;

				other._root = tmp;
				other._end = tmp_end;
				other._size = tmp_size;
				other._allocator = tmp_alloc;
				other._comp = tmp_comp;
			};

			bool	count(const key_type &key) const 
			{
				if (find(key) != NULL)
					return (true);
				return (false);
			};

			iterator	lower_bound (const key_type& key)
			{
				node_type	*tmp = _root;
				node_type	*lower = NULL;

				while (tmp != NULL)
				{
					if (_comp(key, tmp->getValue()))
					{
						lower = tmp;
						tmp = tmp->getLeft();
					}
					else if (_comp(tmp->getValue(), key))
						tmp = tmp->getRight();
					else
						return (iterator(tmp));
				}
				if (lower == NULL)
					return (iterator(_end));
				return (iterator(lower));
			};

			const_iterator	lower_bound (const key_type& key) const
			{
				node_type	*tmp = _root;
				node_type	*lower = NULL;

				while (tmp != NULL)
				{
					if (_comp(key, tmp->getValue()))
					{
						lower = tmp;
						tmp = tmp->getLeft();
					}
					else if (_comp(tmp->getValue(), key))
						tmp = tmp->getRight();
					else
						return (const_iterator(tmp));
				}
				if (lower == NULL)
					return (const_iterator(_end));
				return (const_iterator(lower));
			};

			iterator	upper_bound (const key_type& key)
			{
				node_type	*tmp = _root;
				node_type	*upper = NULL;

				while (tmp != NULL)
				{
					if (_comp(tmp->getValue(), key))
						tmp = tmp->getRight();
					else if (_comp(key, tmp->getValue()))
					{
						upper = tmp;
						tmp = tmp->getLeft();
					}
					else
					{
						if (tmp->getRight() != NULL)
							return (iterator(__findMinimum(tmp->getRight())));
						else if (upper == NULL)
							return (iterator(_end));
						return (iterator(upper));
					}
				}
				if (upper == NULL)
					return (iterator(_end));
				return (iterator(upper));
			};

			const_iterator	upper_bound (const key_type& key) const
			{
				node_type	*tmp = _root;
				node_type	*upper = NULL;

				while (tmp != NULL)
				{
					if (_comp(tmp->getValue(), key))
						tmp = tmp->getRight();
					else if (_comp(key, tmp->getValue()))
					{
						upper = tmp;
						tmp = tmp->getLeft();
					}
					else
					{
						if (tmp->getRight() != NULL)
							return (const_iterator(__findMinimum(tmp->getRight())));
						else if (upper == NULL)
							return (iterator(_end));
						return (const_iterator(upper));
					}
				}
				if (upper == NULL)
					return (const_iterator(_end));
				return (const_iterator(upper));
			};

			ft::pair<iterator, iterator>	equal_range (const key_type& key)
			{
				iterator	lower = lower_bound(key);
				iterator	upper = upper_bound(key);
				return (ft::pair<iterator, iterator>(lower, upper));
			};

			ft::pair<const_iterator, const_iterator>	equal_range (const key_type& key) const
			{
				const_iterator	lower = lower_bound(key);
				const_iterator	upper = upper_bound(key);
				return (ft::pair<const_iterator, const_iterator>(lower, upper));
			};
	};
}