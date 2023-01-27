/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:54 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/27 13:04:11 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iterator>

#include "select_const_type.hpp"

namespace ft
{

	template <typename T, bool IsConst = false>
	class vector_iterator
	{

	public:

		typedef std::random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;
		typedef std::size_t						size_type;

		typedef T															value_type;
		typedef typename ft::select_const_type<IsConst, T*, const T*>::type	pointer;
		typedef typename ft::select_const_type<IsConst, T&, const T&>::type	reference;

	private:

		pointer	_pointer;

	public:
		vector_iterator( pointer pointer = 0 ) : _pointer(pointer) {};
		vector_iterator( const vector_iterator<T> &other ): _pointer(other.getPointer()) { };
		~vector_iterator( ) { };

		vector_iterator &operator=( const vector_iterator &other )
		{
			if (this != &other)
				this->_pointer = other._pointer;
			return *this;
		}

		pointer			getPointer( void ) const { return this->_pointer; }

		reference			operator*() const { return *this->_pointer; }
		pointer				operator->() const { return this->_pointer; }

		vector_iterator&	operator++() { this->_pointer++; return *this; }  
		vector_iterator&	operator--() { this->_pointer--; return *this; }  
		vector_iterator		operator++(int) {
			vector_iterator tmp(*this);
			
			++(*this);
			return tmp;
		}
		vector_iterator		operator--(int) {
			vector_iterator tmp(*this);
			
			--(*this);
			return tmp;
		}

		vector_iterator&	operator+=( int n ) { this->_pointer += n; return *this; }
		vector_iterator&	operator-=( int n ) { this->_pointer -= n; return *this; }
		vector_iterator		operator+( int n ) const { return vector_iterator(_pointer + n); }  
		vector_iterator		operator-( int n ) const { return vector_iterator(_pointer - n); }  

		reference	operator[]( int n ) const { return *(*this + n); }

		friend bool	operator==( const vector_iterator& lhs,
				const vector_iterator& rhs )
		{
			return lhs._pointer == rhs._pointer;
		}
		friend bool	operator!=( const vector_iterator& lhs,
				const vector_iterator& rhs )
		{
			return lhs._pointer != rhs._pointer;
		}
		friend bool	operator<( const vector_iterator& lhs, const vector_iterator& rhs )
		{
			return lhs._pointer < rhs._pointer;
		}
		friend bool	operator<=( const vector_iterator& lhs, const vector_iterator& rhs )
		{
			return lhs._pointer <= rhs._pointer;
		}
		friend bool	operator>( const vector_iterator& lhs, const vector_iterator& rhs )
		{
			return lhs._pointer > rhs._pointer;
		}
		friend bool	operator>=( const vector_iterator& lhs, const vector_iterator& rhs )
		{
			return lhs._pointer >= rhs._pointer;
		}


	};

}