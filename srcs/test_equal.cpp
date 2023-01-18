/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equal.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:32:09 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/18 15:46:04 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "equal.hpp"

extern std::string name;

void	test_equal(void)
{
	std::cout << name << "equal" << std::endl;
	
	int a[] = {1, 2, 3, 4, 5};
	int b[] = {1, 2, 3, 4, 5};
	int b2[] = {1, 2, 3, 4, 6};

	std::string c = "aloalo";
	std::string d = "kayak";

	std::cout << "{1, 2, 3, 4, 5} == {1, 2, 3, 4, 5} : " << ft::equal(a, a + 5, b) << std::endl;
	std::cout << "{1, 2, 3, 4, 5} == {1, 2, 3, 4, 6} : " << ft::equal(a, a + 5, b2) << std::endl;
	std::cout << "aloalo == kayak : " << ft::equal(c.begin(), c.end(), d.begin()) << std::endl;
	std::cout << "kayak == (reverse)kayak : " << ft::equal(d.begin(), d.end(), d.rbegin(), std::equal_to<char>()) << std::endl;
}
