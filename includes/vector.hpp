/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:35 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/30 13:40:05 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstring>

#include <iostream>

#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include "iterator_distance.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

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
			typedef typename ft::vectorIterator<value_type>			iterator;
			typedef typename ft::vectorIterator<const value_type>	const_iterator;
			//typedef pointer			iterator;
			//typedef const_pointer	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			size_type	_size;
			size_type	_capacity;
			pointer		_data;
			Allocator	_allocator;

			template <typename InputIterator>
			void __rangeAssign(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				clear();
				for (; first != last; ++first) {
					push_back(*first);
				}
			};

			template <typename ForwardIterator>
			void __rangeAssign(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				const size_type n = ft::distance(first, last);
				
				clear();
				if (n > _capacity)
					reserve(__new_capacity(n));
				//std::copy(first, last, _data);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_data + i, *first++);
				_size = n;
			};

			template<typename InputIterator>
			void	__rangeInsert(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				if (position == end())
				{
					for (; first != last; ++first)
						push_back(*first);
				}
				else if (first != last)
				{
					vector tmp(first, last);
					insert(position, tmp.begin(), tmp.end());
				}
			};

			template<typename ForwardIterator>
			void	__rangeInsert(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				size_type			dist = ft::distance(begin(), position);
				size_type			n = ft::distance(first, last);

				if (n == 0)
					return ;
				if (position == end())
				{
					for (size_type i = 0; i < n; i++)
						push_back(*first++);
				}
				else
				{
					if (_size + n > _capacity)
						reserve(__new_capacity(_size + n));
					for (int i = _size - 1; i >= (int)dist; i--)
					{
						_allocator.construct(_data + i + n, _data[i]);
						_allocator.destroy(_data + i);
					}
					for (size_type k = dist; k < dist + n; k++)
						_allocator.construct(_data + k, *first++);
					_size += n;
				}
			};

			size_type	__new_capacity(size_type n)
			{
				size_type tmp = _capacity;

				while (tmp < n)
				{
					if (tmp == 0)
						tmp = 1;
					else
						tmp *= 2;	
				}
				return (tmp);
			};

		public:
			/***********************Constructor***********************/
			vector() : _size(0), _capacity(0), _data(NULL), _allocator(Allocator())
			{};

			explicit vector( const Allocator& alloc ) : _size(0), _capacity(0), _data(NULL), _allocator(alloc)
			{};

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _size(0), _capacity(0), _data(NULL), _allocator(alloc)
			{
				if (count == 0)
					return ;
				reserve(count);
				for (size_type i = 0; i < _capacity; i++)
					_allocator.construct(_data + i, value);
				_size = _capacity;
			};

			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) : _size(0), _capacity(0), _data(NULL), _allocator(alloc)
			{
				typedef typename ft::iterator_traits<InputIt>::iterator_category category;

				__rangeAssign(first, last, category());
			};

			vector( const vector& other ) : _size(0), _capacity(0), _data(NULL), _allocator(other.get_allocator())
			{
				if (other.capacity() == 0)
					return ;
				reserve(other.capacity());
				for (size_type i = 0; i < other.size(); i++)
					_allocator.construct(_data + i, other._data[i]);
				_size = other.size();
			};

			~vector()
			{
				clear();
				if (_data)
					_allocator.deallocate(_data, _capacity);
			};

			vector& operator=(const vector& rhs)
			{
				if (this == &rhs)
					return (*this);
				_allocator = rhs.get_allocator();
				clear();
				if (_data != NULL)
					_allocator.deallocate(_data, _capacity);
				_size = rhs.size();
				_capacity = rhs.capacity();
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, rhs._data[i]);
				return (*this);
			};


			/***********************Iterator**************************/
			iterator begin() {return (_data);};
			const_iterator begin() const {return (_data);};

			iterator end() {return (_data + _size);};
			const_iterator end() const {return (_data + _size);};

			reverse_iterator rbegin() {return (reverse_iterator(_data + _size));};
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(_data + _size));};

			reverse_iterator rend() {return (reverse_iterator(_data));};
			const_reverse_iterator rend() const {return (const_reverse_iterator(_data));};

			/***********************Allocator*************************/
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
			void reserve( size_type n )
			{
				pointer	tmp;

				if (n <= _capacity)	return ;
				if (n > max_size())
					throw std::length_error("> max size");
				tmp = _allocator.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(&tmp[i], _data[i]);
					_allocator.destroy(&_data[i]);
				}
				if (_data)
					_allocator.deallocate(_data, _capacity);
				_data = tmp;
				_capacity = n;
			};
			size_type capacity() const {return (_capacity);};


			/***********************Modifier********************************/
			
			template <typename InputIterator>
			void assign(InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
			{
				typedef typename iterator_traits<InputIterator>::iterator_category category;

				__rangeAssign(first, last, category());
			};			

			void assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_data + i, val);
				_size = n;
			};

			void push_back(const value_type& val)
			{
				if (_size == _capacity)
				{
					reserve(__new_capacity(_capacity + 1));
				}
				_allocator.construct(_data + _size, val);
				_size++;
			};

			void pop_back()
			{
				_allocator.destroy(_data + _size - 1);
				_size--;
			};

			iterator insert(iterator position, const value_type& val)
			{
				size_type	tmp = ft::distance(begin(), position);

				insert(position, 1, val);
				return (iterator(&_data[tmp]));
			};
	
		    void insert(iterator position, size_type n, const value_type& val)
			{
				size_type	dist = ft::distance(begin(), position);

				if (n == 0)
					return ;
				if (position == end())
				{
					for (size_type i = 0; i < n; i++)
						push_back(val);
				}
				else
				{
					if (_size + n > _capacity)
						reserve(__new_capacity(_size + n));
					for (int i = _size - 1; i >= (int)dist; i--)
					{						
						_allocator.construct(_data + i + n, _data[i]);
						_allocator.destroy(_data + i);
					}
					for (size_type k = dist; k < dist + n; k++)
						_allocator.construct(_data + k, val);
					_size += n;
				}
			};

	
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
			{
				typedef typename ft::iterator_traits<InputIterator>::iterator_category category;

				__rangeInsert(position, first, last, category());
			};
			
			iterator erase(iterator position)
			{
				size_type	pos = ft::distance(begin(), position);

				std::copy(_data + pos + 1, _data + _size, _data + pos);
				_allocator.destroy(_data + _size - 1);
				_size--;
				return (iterator(&_data[pos]));
			};

			iterator erase(iterator first, iterator last)
			{
				size_type	pos = ft::distance(begin(), first);
				size_type	n = ft::distance(first, last);

				std::copy(_data + pos + n, _data + _size, _data + pos);
				for (size_type i = _size - n; i < _size; i++)
					_allocator.destroy(_data + i);
				_size -= n;
				return (first);
			};
			
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);
				_size = 0;
			};

			void swap(vector& other)
			{
				pointer	tmp_ptr = _data;
				size_type	tmp_size = _size;
				size_type	tmp_capacity = _capacity;
				allocator_type	tmp_allocator = _allocator;
				

				_data = other._data;
				_size = other._size;
				_capacity = other._capacity;
				_allocator = other._allocator;
				other._data = tmp_ptr;
				other._size = tmp_size;
				other._capacity = tmp_capacity;
				other._allocator = tmp_allocator;
				
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n > _size)
				{
					if (n > _capacity)
						reserve(__new_capacity(n));
					for (size_type i = _size; i < n; i++)
						_allocator.construct(_data + i, val);
				}
				else
				{
					for (size_type i = n; i < _size; i++)
						_allocator.destroy(_data + i);
				}
				_size = n;
			};
	};

	/******************Non-member functions************************/
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		typename ft::vector<T, Alloc>::const_iterator it1 = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator it2 = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator e_it1 = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator e_it2 = rhs.end();

		if (lhs.size() != rhs.size())
			return (false);
		while ((it1 != e_it1) && (it2 != e_it2))
		{
			if (!(*it1 == *it2))
				return (false);
			++it1;
			++it2;
		}
		return (true);
	}

	//template< typename T, class Alloc>
	//bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));};

	template< typename T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (!(lhs == rhs));};

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));};

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (rhs < lhs);};

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (!(rhs < lhs));};

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {return (!(lhs < rhs));};

	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	};
}
