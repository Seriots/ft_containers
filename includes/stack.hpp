/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:47:52 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/24 12:07:12 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "vector.hpp" //change this to my vector

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
				typedef T			value_type;
				typedef Container	container_type;
				typedef size_t		size_type;
		
		protected:
				container_type		c;
		
		public:
				/*********************constructor*********************/
				explicit	stack(const container_type& cont = container_type()) : c(cont) {};
				~stack() {};

				stack& operator=( const stack& other ) { c = other.c; return *this; };
				
				/*********************Member Functions*********************/
				bool				empty() const { return (c.empty()); };
				size_type			size() const { return(c.size()); };
				value_type&			top() { return (c.back()); };
				const value_type&	top() const { return (c.back()); };
				void				push (const value_type& val) { c.push_back(val); };
				void				pop() { c.pop_back(); };

				/*********************non-member functions*********************/
				friend bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c == rhs.c); };
				friend bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c != rhs.c); };
				friend bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c < rhs.c); };
				friend bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c <= rhs.c); };
				friend bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c > rhs.c); };
				friend bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c >= rhs.c); };
	};
}
