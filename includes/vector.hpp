/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:09:35 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/18 16:28:40 by lgiband          ###   ########.fr       */
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

			allocator_type get_allocator() const {return allocator_type();};

	};
}