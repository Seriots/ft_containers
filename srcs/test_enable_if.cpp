/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_enable_if.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:25:30 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/17 23:49:36 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <type_traits>
#include <limits>

#include "enable_if.hpp"

extern std::string	name;

template <typename T>
typename ft::enable_if<std::numeric_limits<T>::is_integer, T>::type	multiply(T x)
{
	return (x * x);
}

void	test_enable_if(void)
{
	std::cout << name << "enable_if_test" << std::endl;

	std::cout << multiply(2) << std::endl;
//	std::cout << multiply("yo") << std::endl;
}
