/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:25:50 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/29 13:27:51 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

#include "select_const_type.hpp"

namespace ft
{
	template <class V, bool isConst = false>
	class vectorIterator
	{
			typedef V							value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef typename ft::select_const_type<isConst, value_type*, const value_type*>::type	pointer;
			typedef typename ft::select_const_type<isConst, value_type&, const value_type&>::type	reference;

		private:
			pointer		_ptr;
			
		public:
			vectorIterator() : _ptr(NULL) {}
			vectorIterator(pointer ptr) : _ptr(ptr) {}
			vectorIterator(const vectorIterator &rhs) : _ptr(rhs._ptr) {}
			~vectorIterator() {}

			vectorIterator	&operator=(const vectorIterator &rhs)
			{
				_ptr = rhs._ptr;
				return (*this);
			}

			reference	operator*() const
			{
				return (*_ptr);
			}

			pointer		operator->() const
			{
				return (_ptr);
			}

			vectorIterator	&operator++()
			{
				++_ptr;
				return (*this);
			}

			vectorIterator	operator++(int)
			{
				vectorIterator	tmp(*this);
				++_ptr;
				return (tmp);
			}

			vectorIterator	&operator--()
			{
				--_ptr;
				return (*this);
			}

			vectorIterator	operator--(int)
			{
				vectorIterator	tmp(*this);
				--_ptr;
				return (tmp);
			}

			bool	operator==(const vectorIterator &rhs) const
			{
				return (_ptr == rhs._ptr);
			}

			bool	operator!=(const vectorIterator &rhs) const
			{
				return (_ptr != rhs._ptr);
			}
	};
};