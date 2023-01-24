/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:35 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/24 10:49:46 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <cstring>

#include <iostream>

#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include "enable_if.hpp"

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
				std::memcpy(_data, &(*first), _size * sizeof(T));
				//for (size_type i = 0; i < _size; i++)
				//	_allocator.construct(_data + i, *(first++));
			};

			vector( const vector& other ) : _size(other._size), _capacity(other._capacity), _data(NULL), _allocator(other._allocator)
			{
				_data = _allocator.allocate(_capacity);
				std::memcpy(_data, other._data, _size * sizeof(T));
				//for (size_type i = 0; i < _size; i++)
				//	_allocator.construct(_data + i, other._data[i]);
			};

			~vector()
			{
				this->clear();
				_allocator.deallocate(_data, _capacity);
			};

			vector& operator=(const vector& rhs)
			{
				if (this == &rhs)
					return (*this);
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);
				if (_data != NULL)
					_allocator.deallocate(_data, _capacity);
				_size = rhs._size;
				_capacity = rhs._capacity;
				_data = _allocator.allocate(_capacity);
				std::memcpy(_data, rhs._data, _size * sizeof(T));
				//for (size_type i = 0; i < _size; i++)
				//	_allocator.construct(_data + i, rhs._data[i]);
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
			void reserve( size_type new_cap )
			{
				if (new_cap > this->max_size())
					throw std::length_error("vector");
				if (new_cap <= _capacity)
					return ;
				_capacity = new_cap;
				pointer tmp = _allocator.allocate(_capacity);
				std::memcpy(tmp, _data, _size * sizeof(T));
			};
			size_type capacity() const {return (_capacity);};


			/***********************Modifier********************************/
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);
				if ((size_type)(last - first) > _capacity && _data != NULL)
					_allocator.deallocate(_data, _capacity);
				_size = last - first;
				if ((size_type)(last - first) > _capacity)
				{
					_capacity = last - first;
					_data = _allocator.allocate(_capacity);
				}
			};

			void assign(size_type n, const value_type& val)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_data + i);

				if (n > _capacity && _data != NULL)
					_allocator.deallocate(_data, _capacity);
				_size = n;
				if (n > _capacity)
				{
					_capacity = n;
					_data = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_data + i, value_type(val));
			};

			void push_back(const value_type& val)
			{
				if (_size == _capacity)
				{
					if (_capacity == 0)
						_capacity = 1;
					else
						_capacity *= 2;
					pointer tmp = _allocator.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(tmp + i, _data[i]);
					_allocator.deallocate(_data, _capacity / 2);
					_data = tmp;
				}
				_allocator.construct(_data + _size, val);
				_size++;
			};

			void pop_back()
			{
				//if (_size == 0) //std doesnt protect that
				//	return ;
				_allocator.destroy(_data + _size - 1);
				_size--;
			};

			iterator insert(iterator position, const value_type& val)
			{
				size_type	pos;

				pos = position - _data;
				
				if (_size == _capacity)
				{
					if (_capacity == 0)
						_capacity = 1;
					else
						_capacity *= 2;
					pointer tmp = _allocator.allocate(_capacity);

					std::memcpy(tmp, _data, sizeof(value_type) * pos);
					_allocator.construct(tmp + pos, val);
					std::memcpy(tmp + pos + 1, _data + pos, sizeof(value_type) * (_size - pos));
					
					_allocator.deallocate(_data, _capacity / 2);
					_data = tmp;
				}
				else
				{
					std::memcpy(_data + pos + 1, _data + pos, sizeof(value_type) * (_size - pos));
					_allocator.construct(_data + pos, val);
				}
				_size++;
				return (position);
			};
	
		    void insert(iterator position, size_type n, const value_type& val)
			{
				size_type	pos;
				size_type	previous_capacity = _capacity;

				pos = position - _data;
				
				if (_size + n > _capacity)
				{
					_capacity = _size + n;
					pointer tmp = _allocator.allocate(_capacity);

					std::memcpy(tmp, _data, sizeof(value_type) * pos);
					for (size_type i = 0; i < n; i++)
						_allocator.construct(tmp + pos + i, val);
					std::memcpy(tmp + pos + n, _data + pos, sizeof(value_type) * (_size - pos));
					
					_allocator.deallocate(_data, previous_capacity);
					_data = tmp;
				}
				else
				{
					std::memcpy(_data + pos + n, _data + pos, sizeof(value_type) * (_size - pos));
					for (size_type i = 0; i < n; i++)
						_allocator.construct(_data + pos + i, val);
				}
				_size += n;
			};
	
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type	pos;
				size_type	previous_capacity = _capacity;

				pos = position - _data;
				size_type n = last - first;				
				if (_size + n > _capacity)
				{
					if (_capacity == 0)
						_capacity = n;
					else if (_capacity < n)
						_capacity = _size + n;
					else
						_capacity = _size + (n * ((size_type)((_capacity) / n) + 1));
					pointer tmp = _allocator.allocate(_capacity);

					std::memcpy(tmp, _data, sizeof(value_type) * pos);
					for (size_type i = 0; i < n; i++)
						_allocator.construct(tmp + pos + i, *(first + i));
					std::memcpy(tmp + pos + n, _data + pos, sizeof(value_type) * (_size - pos));
					
					_allocator.deallocate(_data, previous_capacity);
					_data = tmp;
				}
				else
				{
					std::memcpy(_data + pos + n, _data + pos, sizeof(value_type) * (_size - pos));
					for (size_type i = 0; i < n; i++)
						_allocator.construct(_data + pos + i, *(first + i));
				}
				_size += n;
			};
			
			iterator erase(iterator position)
			{
				size_type	pos;

				pos = position - _data;
				_allocator.destroy(_data + pos);
				std::memcpy(_data + pos, _data + pos + 1, sizeof(value_type) * (_size - pos - 1));
				_size--;
				return (position);
			};

			iterator erase(iterator first, iterator last)
			{
				size_type	pos;
				size_type	n;

				pos = first - _data;
				n = last - first;
				for (size_type i = 0; i < n; i++)
					_allocator.destroy(_data + pos + i);
				std::memcpy(_data + pos, _data + pos + n, sizeof(value_type) * (_size - pos - n));
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
				if (n > _capacity)
				{
					_capacity = n;
					pointer tmp = _allocator.allocate(_capacity);
					std::memcpy(tmp, _data, sizeof(value_type) * _size);
					for (size_type i = _size; i < n; i++)
						_allocator.construct(tmp + i, val);
					_allocator.deallocate(_data, _capacity);
					_data = tmp;
				}
				else
				{
					for (size_type i = _size; i < n; i--)
						_allocator.destroy(_data + i);
				}
				_size = n;
			}

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