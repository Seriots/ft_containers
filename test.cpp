/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:06:53 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/18 12:45:28 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

#include "is_integral.hpp"

void	comparison_operator_test(void)
{
	std::cout << ft::is_integral<int>::value << std::endl;

	std::cout << ft::is_integral<float>::value << std::endl;

	std::cout << ft::is_integral<std::string>::value << std::endl;
}

int	main(void)
{
	comparison_operator_test();
	comparison_operator_test2();
}