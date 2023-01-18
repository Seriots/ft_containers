/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reverse_iterator.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:53:53 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/17 13:54:55 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

#include "reverse_iterator.hpp"

extern std::string name;

void	comparison_operator_test(void)
{
	int a[] = {0, 1, 2, 3};
	std::cout << "<Set: array, 0->1->2->3>" << std::endl;
	
	std::cout << "<Comparison operators>" << std::endl;
    ft::reverse_iterator<int*> x(a + 4);
	ft::reverse_iterator<int*> y(a + 4);
	ft::reverse_iterator<int*> z(a + 3);
 
    std::cout
        << std::boolalpha
        << "*x == " << *x << '\n' // 3
        << "*y == " << *y << '\n' // 3
        << "*z == " << *z << '\n' // 2
        << "x == y ? " << (x == y) << '\n' // true
        << "x != y ? " << (x != y) << '\n' // false
        << "x <  y ? " << (x <  y) << '\n' // false
        << "x <= y ? " << (x <= y) << '\n' // true
        << "x == z ? " << (x == z) << '\n' // false
        << "x != z ? " << (x != z) << '\n' // true
        << "x <  z ? " << (x <  z) << '\n' // true
        << "x <= z ? " << (x <= z) << '\n' // true
		;
	
	std::cout << "<Edit: z--, y++>" << std::endl;
	z--;
	y++;
	std::cout
        << std::boolalpha
        << "*x == " << *x << '\n' // 3
        << "*y == " << *y << '\n' // 3
        << "*z == " << *z << '\n' // 2
        << "x == y ? " << (x == y) << '\n' // true
        << "x != y ? " << (x != y) << '\n' // false
        << "x <  y ? " << (x <  y) << '\n' // false
        << "x <= y ? " << (x <= y) << '\n' // true
        << "x == z ? " << (x == z) << '\n' // false
        << "x != z ? " << (x != z) << '\n' // true
        << "x <  z ? " << (x <  z) << '\n' // true
        << "x <= z ? " << (x <= z) << '\n' // true
		;
	
}

void	modification_operator_test(void)
{
	std::cout << "<Modification operators>" << std::endl;
	std::vector<int> v;

	std::cout << "<Set: std::vector, 1->2->3->4->5>" << std::endl;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std::cout << "<Set: x:end, y:begin>" << std::endl;

	ft::reverse_iterator<std::vector<int>::iterator> x(v.end());
	ft::reverse_iterator<std::vector<int>::iterator> y(v.begin());
	
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	for (int i = 0; i < 6; i++)
	{
		std::cout << "<Edit: x++, y++>" << std::endl;
		x++;
		y++;
		std::cout << "*x == " << *x << std::endl;
		std::cout << "*y == " << *y << std::endl;
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << "<Edit: x--, y-->" << std::endl;
		x--;
		y--;
		std::cout << "*x == " << *x << std::endl;
		std::cout << "*y == " << *y << std::endl;
	}
	std::cout << "<Edit: x + 4, y + 4>" << std::endl;
	x = x + 4;
	y = y + 4;
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	std::cout << "<Edit: x - 1, y - 1>" << std::endl;
	x = x - 1;
	y = x - 1;
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	std::cout << "<Edit: x += 4, y += 4>" << std::endl;
	x += 4;
	y += 4;
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	std::cout << "<Edit: x -= 1, y -= 1>" << std::endl;
	x -= 1;
	y -= 1;
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	std::cout << "<Edit: --x, --y>" << std::endl;
	std::cout << "*--x == " << *--x << ", *x ==" << *x << std::endl;
	std::cout << "*--y == " << *--y << ", *y ==" << *y << std::endl;
	std::cout << "<Edit: ++x, ++y>" << std::endl;
	std::cout << "*++x == " << *++x << ", *x ==" << *x << std::endl;
	std::cout << "*++y == " << *++y << ", *y ==" << *y << std::endl;
	std::cout << "<Edit: x--, y-->" << std::endl;
	std::cout << "*x-- == " << *x-- << ", *x ==" << *x << std::endl;
	std::cout << "*y-- == " << *y-- << ", *y ==" << *y << std::endl;
	std::cout << "<Edit: x++, y++>" << std::endl;
	std::cout << "*x++ == " << *x++ << ", *x ==" << *x << std::endl;
	std::cout << "*y++ == " << *y++ << ", *y ==" << *y << std::endl;
}

void	access_operator_test(void)
{
	std::cout << "<Modification operators>" << std::endl;
	std::vector<int> v;

	std::cout << "<Set: std::vector, 1->2->3->4->5>" << std::endl;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	ft::reverse_iterator<std::vector<int>::iterator> x(v.end());
	
	std::cout << "*x == " << *x << std::endl;
	std::cout << "x[0] == " << *x[0] << std::endl;
	std::cout << "x[1] == " << *x[1] << std::endl;
	std::cout << "x[4] == " << *x[4] << std::endl;
	std::cout << "(&x)->base() == " << *((&(x))->base()) << std::endl;
	std::cout << "<Edit: x++>" << std::endl;
	x++;
	std::cout << "(&x)->base() == " << *((&(x))->base()) << std::endl;
}

void	constructor_test(void)
{
	std::cout << "<Constructor reverse_iterator test>" << std::endl;
	std::vector<int> v;

	std::cout << "<Set: std::vector, 1->2->3->4->5>" << std::endl;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std::cout << "<Set: x:end, y:begin>" << std::endl;
	ft::reverse_iterator<std::vector<int>::iterator> x(v.end());
	ft::reverse_iterator<std::vector<int>::iterator> y;
	ft::reverse_iterator<std::vector<int>::iterator> z(x);

	y = x;
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	std::cout << "*z == " << *z << std::endl;
	std::cout << std::boolalpha << "x == y : " << (x == y) << std::endl;
	std::cout << std::boolalpha << "x == z : " << (x == z) << std::endl;
	std::cout << std::boolalpha << "y == z : " << (y == z) << std::endl;
	
	std::cout << "<Edit: x++>" << std::endl;
	x++;
	std::cout << "*x == " << *x << std::endl;
	std::cout << "*y == " << *y << std::endl;
	std::cout << "*z == " << *z << std::endl;
	std::cout << std::boolalpha << "x == y : " << (x == y) << std::endl;
	std::cout << std::boolalpha << "x == z : " << (x == z) << std::endl;
	std::cout << std::boolalpha << "y == z : " << (y == z) << std::endl;
	
}

void	reverse_iterator_test(void)
{
	std::cout << name << "reverse_iterator_test" << std::endl;
	
	constructor_test();
	comparison_operator_test();
	modification_operator_test();
	access_operator_test();
}