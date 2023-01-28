/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_distance.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:59:06 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/28 14:06:34 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

namespace ft
{
	template <typename Iterator>
	size_t iteratorDistance(Iterator first, Iterator last)
	{
		size_t	size = 0;
		
		while (first != last)
		{
			first++;
			size ++;
		}
		return (size);
	};
};
