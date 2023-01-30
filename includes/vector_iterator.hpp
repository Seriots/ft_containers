/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:25:50 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/30 18:15:29 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

namespace ft
{
	template <typename V>
	class vectorIterator
	{
		public:
			typedef V								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef V* 								pointer;
			typedef V& 								reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
		private:
			pointer		_ptr;
			
		public:
			vectorIterator( const vectorIterator<V> &other ): _ptr(other.base()) { return; }
			vectorIterator( pointer ptr = 0 ) : _ptr(ptr) { return; }
			~vectorIterator( void ) { return; }

			vectorIterator &operator=( const vectorIterator &other )
			{
				if (this != &other)
					this->_ptr = other.base();
				return *this;
			}

			pointer	base( void ) const { return (this->_ptr); }

			reference	operator*() const { return (*_ptr); }
			pointer		operator->() const { return (_ptr); }
			reference	operator[](difference_type n) { return (*(*this + n)); };

			vectorIterator	&operator++() { ++_ptr; return (*this); }
			vectorIterator	operator++(int) { vectorIterator	tmp(*this); ++_ptr; return (tmp); }
			vectorIterator	&operator--() { --_ptr; return (*this); }
			vectorIterator	operator--(int) { vectorIterator	tmp(*this); --_ptr; return (tmp); }
			vectorIterator	operator+(difference_type n) const { return (vectorIterator(_ptr + n)); }
			vectorIterator	operator-(difference_type n) const { return (vectorIterator(_ptr - n));}
			vectorIterator	&operator+=(difference_type n) { _ptr += n; return (*this); }
			vectorIterator	&operator-=(difference_type n) {_ptr -= n; return (*this); }

			operator vectorIterator<const value_type>() { return (vectorIterator<const value_type>(_ptr));}

			friend vectorIterator	operator+(difference_type n, const vectorIterator &rhs) { return (vectorIterator(rhs.base() + n)); }
			friend vectorIterator	operator-(difference_type n, const vectorIterator &rhs) { return (vectorIterator(rhs.base() - n)); }
			friend difference_type	operator- (const vectorIterator &lhs, const vectorIterator &rhs) { return (lhs._ptr - rhs._ptr); }

			bool	operator==( const vectorIterator<const value_type>& rhs ) const { return _ptr == rhs.base(); }	
			bool	operator!=( const vectorIterator<const value_type>& rhs ) const { return _ptr != rhs.base(); }
			bool	operator<( const vectorIterator<const value_type>& rhs ) const { return _ptr < rhs.base(); }
			bool	operator<=( const vectorIterator<const value_type>& rhs ) const { return _ptr <= rhs.base(); }
			bool	operator>( const vectorIterator<const value_type>& rhs ) const { return _ptr > rhs.base(); }
			bool	operator>=( const vectorIterator<const value_type>& rhs ) const { return _ptr >= rhs.base(); }
	};

	template <class It1, class It2>
	bool operator==( const vectorIterator<It1>& lhs, const vectorIterator<It2>& rhs ) { return (lhs.base() == rhs.base()); };

	template <class It1, class It2>
	bool operator!=( const vectorIterator<It1>& lhs, const vectorIterator<It2>& rhs ) { return (lhs.base() != rhs.base()); };

	template <class It1, class It2>
	bool operator<( const vectorIterator<It1>& lhs, const vectorIterator<It2>& rhs ) { return (lhs.base() < rhs.base()); };

	template <class It1, class It2>
	bool operator<=( const vectorIterator<It1>& lhs, const vectorIterator<It2>& rhs ) { return (lhs.base() <= rhs.base()); };

	template <class It1, class It2>
	bool operator>( const vectorIterator<It1>& lhs, const vectorIterator<It2>& rhs ) { return (lhs.base() > rhs.base()); };

	template <class It1, class It2>
	bool operator>=( const vectorIterator<It1>& lhs, const vectorIterator<It2>& rhs ) { return (lhs.base() >= rhs.base()); };
	
};
