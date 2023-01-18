/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:24:47 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/18 12:51:16 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>

#define TEST(x, y) ((x == y) ? "\033[32mOK\033[0m --> found " + to_string(y) + " and " + to_string(x) : "\033[31mKO\033[0m --> found " + to_string(y) + " instead of " + to_string(x))

template < typename T > std::string to_string( const T& n )
{
	std::ostringstream stm ;
	stm << n ;
	return stm.str() ;
}


void	stack_test_with_vector(void);
void	stack_test_with_deque(void);
void	reverse_iterator_test(void);
void	test_enable_if(void);
void	test_is_integral(void);

