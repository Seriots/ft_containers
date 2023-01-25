/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:15:19 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/25 21:10:59 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator 													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

		protected:
			iterator_type current;

		public:
			/*******************Constructor*******************/
			reverse_iterator(): current() {};
			explicit reverse_iterator( iterator_type x ): current(x) {};

			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ): current(other.base()) {};

			/*********************Access function*********************/
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other ) { this->current = other.base(); return (*this); };

			iterator_type base() const { return (this->current); };
			reference operator*() const { return (*(this->base() - 1)); };
			pointer operator->() const { return (&(*(this->base() - 1))); };
			reference operator[](difference_type n) const { return *((*this) + n); };
			
			/*******************Manipulation Function*******************/
			reverse_iterator& operator++() { --this->current; return (*this); };
			reverse_iterator operator++(int) { reverse_iterator tmp(*this); --this->current; return (tmp); };
			reverse_iterator& operator--() { ++this->current; return (*this); };
			reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++this->current; return (tmp); };
			reverse_iterator operator+( difference_type n ) const { return (reverse_iterator(this->base() - n)); };
			reverse_iterator& operator+=( difference_type n ) { this->current -= n; return (*this); };
			reverse_iterator operator-( difference_type n ) const { return (reverse_iterator(this->base() + n)); };
			reverse_iterator& operator-=( difference_type n ) { this->current += n; return (*this); };
			
			/*******************Non-member Functions*******************/
			friend bool operator==( const reverse_iterator& lhs, const reverse_iterator& rhs ) { return (lhs.base() == rhs.base()); };
			friend bool operator!=( const reverse_iterator& lhs, const reverse_iterator& rhs ) { return (lhs.base() != rhs.base()); };
			friend bool operator<( const reverse_iterator& lhs, const reverse_iterator& rhs ) { return (lhs.base() > rhs.base()); };
			friend bool operator<=( const reverse_iterator& lhs, const reverse_iterator& rhs ) { return (lhs.base() >= rhs.base()); };
			friend bool operator>( const reverse_iterator& lhs, const reverse_iterator& rhs ) { return (lhs.base() < rhs.base()); };
			friend bool operator>=( const reverse_iterator& lhs, const reverse_iterator& rhs ) { return (lhs.base() <= rhs.base()); };
	};
}