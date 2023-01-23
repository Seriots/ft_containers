/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:35 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/19 13:37:13 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "reverse_iterator.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
			
		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef	typename Allocator::pointer				pointer;
			typedef	typename Allocator::const_pointer		const_pointer;
			typedef pointer									iterator;
			typedef const_pointer							const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		private:
			size_type	_size;
			size_type	_capacity;
			pointer		_data;
			Allocator	_allocator;
		
		public:
			/***********************Constructor***********************/
			vector() : _size(0), _capacity(0), _data(NULL), _allocator(Allocator())
			{};
			
			explicit vector( const Allocator& alloc ) : _size(0), _capacity(0), _data(NULL), _allocator(alloc)
			{};
			
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _size(count), _capacity(count), _data(NULL), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, value);
			};
			
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _size(last - first), _capacity(last - first), _data(NULL), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, *(first++));
			};
			
			vector( const vector& other ) : _size(other._size), _capacity(other._capacity), _data(NULL), _allocator(other._allocator)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, other._data[i]);
			};

			~vector() {_allocator.deallocate(_data, _capacity);};
			/***************************************************************/

			/***********************Member Function*************************/
			allocator_type get_allocator() const {return (_allocator);};

			/***********************Element Access**************************/
			reference operator[]( size_type pos ) {return (_data[pos]);};
			const_reference operator[]( size_type pos ) const {return (_data[pos]);};

			reference at( size_type pos ) {if (pos >= _size) throw std::out_of_range("vector"); return (_data[pos]);};
			const_reference at( size_type pos ) const {if (pos >= _size) throw std::out_of_range("vector"); return (_data[pos]);};

			reference front() {return (_data[0]);};
			const_reference front() const {return (_data[0]);};
			
			reference back() {return (_data[_size - 1]);};
			const_reference back() const {return (_data[_size - 1]);};

			T* data() {return (_data);};
			const T* data() const {return (_data);};
			/************************Iterators******************************/

			/***********************Capacity********************************/
			bool empty() const {return (_size == 0);};
			size_type size() const {return (_size);};
			size_type max_size() const {return (_allocator.max_size());};
			void reserve( size_type new_cap )
			{
				if (new_cap > this->max_size())
					throw std::length_error("vector");
				if (new_cap <= _capacity)
					return ;
				_capacity = new_cap;
				pointer tmp = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(tmp + i, _data[i]);
			};
			size_type capacity() const {return (_capacity);};
	};
}