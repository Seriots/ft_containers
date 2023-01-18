/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:06:53 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/17 13:07:32 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>


void	comparison_operator_test(void)
{
	std::cout << "<Comparison operators>" << std::endl;
	int a[] = {0, 1, 2, 3};
	int b[] = {3, 2, 1, 0};
 
    std::reverse_iterator<int*> x(a + 1);
	std::reverse_iterator<int*> y(b + 1);
 
    std::cout
        << std::boolalpha
        << "*x == " << *x << '\n' // 3
        << "*y == " << *y << '\n' // 3
		<< "x == y ? " << (x == y) << '\n' // true
		;
}

int	main(void)
{
	comparison_operator_test();
}