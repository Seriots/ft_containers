/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_distance.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:59:06 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/29 13:25:25 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	typename ft::iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last)
	{
		typename ft::iterator_traits<Iterator>::difference_type	size = 0;
		Iterator tmp = Iterator(first);
		
		while (tmp != last)
		{
			tmp++;
			size++;
		}
		return (size);
	};
};
