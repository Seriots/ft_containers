/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:35 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/28 20:07:25 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstring>

#include <iostream>

#include "reverse_iterator.hpp"
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
			typedef pointer			iterator;
			typedef const_pointer	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			size_type	_size;
			size_type	_capacity;
			pointer		_data;
			Allocator	_allocator;

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

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _size(count), _capacity(count), _data(NULL), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, value);
			};

			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) : _size(ft::distance(first, last)), _capacity(ft::distance(first, last)), _data(NULL), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				//std::memcpy(_data, first, _size * sizeof(T));
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, value_type(*(first++)));
			};

			vector( const vector& other ) : _size(other._size), _capacity(other._capacity), _data(NULL), _allocator(other._allocator)
			{
				_data = _allocator.allocate(_size);
				//std::memcpy(_data, other._data, _size * sizeof(T));
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, other._data[i]);
			};

			~vector()
			{
				this->clear();
				if (_data)
					_allocator.deallocate(_data, _capacity);
			};

			vector& operator=(const vector& rhs)
			{
				if (this == &rhs)
					return (*this);
				_allocator = rhs.get_allocator();
				if (_data != NULL)
					_allocator.deallocate(_data, _capacity);
				_size = rhs.size();
				_capacity = rhs.capacity();
				_data = _allocator.allocate(_capacity);
				//std::memcpy(_data, rhs._data, _size * sizeof(T));
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
			template <class InputIterator>
			void		assign( InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
			{
				size_type	n = ft::distance(first, last);

				clear();
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_data + i, *first++);
				_size = n;
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
					if (_capacity == 0)
						reserve(1);
					else
						reserve(_capacity * 2);
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
				size_type			i = ft::distance(begin(), position);

				if ((_size + n) > _capacity)
					reserve(__new_capacity(_size + n));
				// for (size_type j = n + _size - 1; j > i + n - 1; j--)
				// {
				// 	_allocator.construct(&_data[j], _data[j - n]);
				// 	_allocator.destroy(&_data[j - n]);
				// }
				std::copy(_data + i, _data + _size, _data + i + n);
				for (size_type k = i; k < i + n; k++)
				{
					_allocator.construct(&_data[k], val);
					_size++;
				}
			};
	
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
			{
				size_type			i = ft::distance(begin(), position);
				size_type			n = ft::distance(first, last);

				if ((_size + n) > _capacity)
					reserve(__new_capacity(_size + n));
				// for (size_type j = n + _size - 1; j > i + n - 1; j--)
				// {
				// 	_allocator.construct(&_data[j], _data[j - n]);
				// 	_allocator.destroy(&_data[j - n]);
				// }
				std::copy(_data + i, _data + _size, _data + i + n);
				for (size_type k = i; k < i + n; k++)
				{
					_allocator.construct(&_data[k], *first++);
					_size++;
				}
			};
			
			iterator erase(iterator position)
			{
				size_type	pos;

				pos = position - _data;
				_allocator.destroy(_data + pos);
				// for (size_type i = pos; i < _size - 1; i++)
				// 	_allocator.construct(_data + i, _data[i + 1]);
				std::copy(_data + pos + 1, _data + _size, _data + pos);
				_size--;
				return (position);
			};

			iterator erase(iterator first, iterator last)
			{
				size_type	pos = ft::distance(begin(), first);
				size_type	n = ft::distance(first, last);

				for (size_type i = 0; i < n; i++)
					_allocator.destroy(_data + pos + i);
				// for (size_type i = pos; i < _size - n; i++)
				// {
				// 	std::cerr << "capacity: " << _capacity << ", size: " << _size << ", pos: " << pos << ", n: " << n << ", i: " << i << std::endl;
				//   	_allocator.construct(_data + i, _data[i + n]);
				// }
				std::copy(_data + pos + n, _data + _size, _data + pos);
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
				vector	tmp(other);
				other = *this;
				*this = tmp;
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
		ft::vector<T, Alloc> tmp(x);
		x = y;
		y = tmp;
	};
}
