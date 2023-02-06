/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:24:47 by lgiband           #+#    #+#             */
/*   Updated: 2023/02/06 11:03:40 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <fstream>

#define TEST(x, y) ((x == y) ? "\033[32mOK\033[0m --> found " + to_string(y) + " and " + to_string(x) : "\033[31mKO\033[0m --> found " + to_string(y) + " instead of " + to_string(x))

template < typename T > std::string to_string( const T& n )
{
	std::ostringstream stm ;
	stm << n ;
	return stm.str() ;
}

std::string	progressBar(long unsigned int value, long unsigned int max_value, long unsigned int size_max, char c);
void	time_test(void f(std::ofstream &), std::ofstream& out);

void	stack_test_with_vector(std::ofstream &out);
void	stack_test_with_deque(std::ofstream &out);
void	reverse_iterator_test(std::ofstream &out);
void	test_enable_if(std::ofstream &out);
void	test_is_integral(std::ofstream &out);
void	test_equal(std::ofstream &out);
void	test_lexicographical_compare(std::ofstream &out);
void	test_vector(std::ofstream &out);
void	test_pair(std::ofstream& out);
void	test_map(std::ofstream &out);
void	test_set(std::ofstream &out);


