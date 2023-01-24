/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:34 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/24 14:35:46 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "pair.hpp"
#include "reverse_iterator.hpp"


namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key				 							key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::iterator			iterator;
			typedef typename allocator_type::const_iterator		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;

			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			value_compare value_comp() const {return value_compare(_comp);};

		private:
			allocator_type		_allocator;
			key_compare			_comp;
			size_type			_size;
			

		public:
			/*************************Contructor*******************************/
			map() : _allocator(Allocator()), _comp(Compare()), _size(0), _begin(NULL), _end(NULL), _root(NULL), _leftmost(NULL), _rightmost(NULL) {_root = _allocator.allocate(1);};

			explicit map( const Compare& comp, const Allocator& alloc = Allocator() );

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() );

	 		map( const map& other );
			
			/*************************Iterators********************************/
			/*************************Capacity*********************************/
			/*************************Element Access***************************/
			/*************************Modifiers********************************/
			/*************************Observers********************************/
			/*************************Operations*******************************/
			/*************************Allocator********************************/
			

	};
}