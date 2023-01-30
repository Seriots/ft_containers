/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:51:11 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/30 18:16:23 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "rbtree_node.hpp"

namespace ft
{
	template <class V>
	class rbTreeIterator
	{
		public:
			typedef V								value_type;
			typedef ft::node<value_type>			node_type;
			typedef std::ptrdiff_t					difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef value_type*						pointer;
			typedef value_type&						reference;

		private:
			node_type	*_node;
			
			node_type	*__getSuccessor(node_type *node)
			{
				node_type	*tmp = node;

				if (tmp == NULL)
				{
					return (NULL);
				}
				if (tmp->getParent() == NULL)
				{
					while (tmp->getLeft() != NULL)
						tmp = tmp->getLeft();
					return (tmp);
				}
				else if (tmp->getRight() != NULL)
				{
					tmp = tmp->getRight();
					while (tmp->getLeft() != NULL)
						tmp = tmp->getLeft();
					return (tmp);
				}
				else
				{
					while (tmp->getParent() != NULL && tmp->getParent()->getRight() == tmp)
					{
						tmp = tmp->getParent();
					}
					if (tmp->getParent() == NULL)
						return (tmp);
					return (tmp->getParent());
				}
			};

			node_type	*__getPredecessor(node_type *node)
			{
				node_type	*tmp = node;

				if (tmp == NULL)
				{
					return (NULL);
				}
				if (tmp->getParent() == NULL)
				{
					while (tmp->getRight() != NULL)
						tmp = tmp->getRight();
					return (tmp);
				}
				else if (tmp->getLeft() != NULL)
				{
					tmp = tmp->getLeft();
					while (tmp->getRight() != NULL)
						tmp = tmp->getRight();
					return (tmp);
				}
				else
				{
					while (tmp->getParent() != NULL && tmp->getParent()->getLeft() == tmp)
						tmp = tmp->getParent();
					return (tmp->getParent());
				}
			};

		public:
			rbTreeIterator(void): _node(NULL) {};
			rbTreeIterator(node_type *node): _node(node) {};
			rbTreeIterator(const rbTreeIterator &rhs): _node(rhs._node) {};
			
			~rbTreeIterator(void) {};
	
			rbTreeIterator &operator=(const rbTreeIterator &other)
			{
				if (this != &other)
					_node = other.base();
				return (*this);
			};

			node_type	*base() const { return (_node); };			

			reference	operator*() const { return (_node->getValue()); };
			pointer		operator->() const { return (&_node->getValue()); };
			reference	operator[](difference_type n) { return (*(*this + n)); };

			rbTreeIterator &operator++() { _node = __getSuccessor(_node); return (*this); };
			rbTreeIterator operator++(int) { rbTreeIterator	tmp(*this); _node = __getSuccessor(_node); return (tmp); };
			rbTreeIterator &operator+=(int n) { while (n-- && _node != NULL) _node = __getSuccessor(_node); return (*this); };
			rbTreeIterator operator+(int n) { rbTreeIterator	tmp(*this); while (n-- && tmp._node != NULL) tmp._node = __getSuccessor(tmp._node); return (tmp); };
			rbTreeIterator &operator--() { _node = __getPredecessor(_node); return (*this); };
			rbTreeIterator operator--(int) { rbTreeIterator	tmp(*this); _node = __getPredecessor(_node); return (tmp); };
			rbTreeIterator &operator-=(int n) { while (n-- && _node != NULL) _node = __getPredecessor(_node); return (*this); };
			rbTreeIterator operator-(int n) { rbTreeIterator	tmp(*this); while (n-- && tmp._node != NULL) tmp._node = __getPredecessor(tmp._node); return (tmp); };

			operator rbTreeIterator<const value_type>() { return (rbTreeIterator<const value_type>(this->base()));}

			friend rbTreeIterator	operator+(difference_type n, const rbTreeIterator &rhs) { return (rbTreeIterator(rhs.base() + n)); }
			friend rbTreeIterator	operator-(difference_type n, const rbTreeIterator &rhs) { return (rbTreeIterator(rhs.base() - n)); }
			friend difference_type	operator-(const rbTreeIterator &lhs, const rbTreeIterator &rhs) { return (lhs.base() - rhs.base()); }

			
			bool	operator==( const rbTreeIterator<const value_type>& rhs ) const { return this->base() == rhs.base(); }	
			bool	operator!=( const rbTreeIterator<const value_type>& rhs ) const { return this->base() != rhs.base(); }
			bool	operator<( const rbTreeIterator<const value_type>& rhs ) const { return this->base() < rhs.base(); }
			bool	operator<=( const rbTreeIterator<const value_type>& rhs ) const { return this->base() <= rhs.base(); }
			bool	operator>( const rbTreeIterator<const value_type>& rhs ) const { return this->base() > rhs.base(); }
			bool	operator>=( const rbTreeIterator<const value_type>& rhs ) const { return this->base() >= rhs.base(); }
	};

	template <class It1, class It2>
	bool operator==( const rbTreeIterator<It1>& lhs, const rbTreeIterator<It2>& rhs ) { return (lhs.base() == rhs.base()); };

	template <class It1, class It2>
	bool operator!=( const rbTreeIterator<It1>& lhs, const rbTreeIterator<It2>& rhs ) { return (lhs.base() != rhs.base()); };

	template <class It1, class It2>
	bool operator<( const rbTreeIterator<It1>& lhs, const rbTreeIterator<It2>& rhs ) { return (lhs.base() < rhs.base()); };

	template <class It1, class It2>
	bool operator<=( const rbTreeIterator<It1>& lhs, const rbTreeIterator<It2>& rhs ) { return (lhs.base() <= rhs.base()); };

	template <class It1, class It2>
	bool operator>( const rbTreeIterator<It1>& lhs, const rbTreeIterator<It2>& rhs ) { return (lhs.base() > rhs.base()); };

	template <class It1, class It2>
	bool operator>=( const rbTreeIterator<It1>& lhs, const rbTreeIterator<It2>& rhs ) { return (lhs.base() >= rhs.base()); };

}